/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:02:27 by abourin           #+#    #+#             */
/*   Updated: 2019/10/25 16:22:36 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_buffer_in_content(char *buffer, char **content)
{
	int		i;
	char	*copy;
	int		c_size;

	i = 0;
	c_size = 0;
	while (buffer[c_size])
	{
		c_size++;
	}
	while ((*content)[i])
	{
		c_size++;
		i++;
	}
	if (!(copy = malloc(sizeof(char) * (c_size + 1))))
	{
		free(*content);
		return (NULL);
	}
	copy[0] = '\0';
	copy = ft_strconcat(copy, *content);
	copy = ft_strconcat(copy, buffer);
	free(*content);
	return (copy);
}

void	ft_set_buffer_end_in_content(char *buffer, char **content,
						int buff_len, int nl_index)
{
	int		i;
	int		j;
	char	*copy;

	if (!(copy = malloc(sizeof(char) * (buff_len - nl_index + 1))))
		return ;
	i = nl_index;
	j = 0;
	while (buffer[i] && i < buff_len)
	{
		copy[j] = buffer[i];
		j++;
		i++;
	}
	copy[j] = '\0';
	free(*content);
	*content = copy;
}

int		ft_buffer_in_line(char *buffer, char **content, char **line)
{
	int		i;
	int		j;
	int		buff_len;

	i = 0;
	buff_len = 0;
	while ((*content)[i])
		i++;
	while (buffer[buff_len] && buff_len < ft_get_newline_index(buffer))
		buff_len++;
	if (!(*line = malloc(sizeof(char) * (i + buff_len + 1))))
		return (-1);
	j = ft_write_line(content, buffer, line);
	ft_set_buffer_end_in_content(buffer,
				content, ft_strlen_or_free(buffer, 0, NULL), j + 1);
	return (1);
}

int		ft_write_line_until_nl(char **content, char **line, int l_index)
{
	int		i;
	char	*copy;
	char	*n_content;

	i = -1;
	if (!(copy = malloc(sizeof(char) * (l_index + 1))))
		return (-1);
	while ((*content)[++i] && i < l_index)
		copy[i] = (*content)[i];
	copy[i] = '\0';
	*line = copy;
	if (ft_strlen_or_free(*content, 0, NULL) == l_index)
		return (ft_strlen_or_free(NULL, 1, content));
	i = l_index;
	if (!(n_content = malloc(sizeof(char)
				* (ft_strlen_or_free(*content, 0, NULL) - l_index + 1))))
		return (-1);
	while ((*content)[++i])
		n_content[i - l_index - 1] = (*content)[i];
	n_content[i - l_index - 1] = '\0';
	free(*content);
	*content = n_content;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*s_temp = NULL;
	char			buff[BUFFER_SIZE + 1];
	int				b_read;
	int				l_index;

	if (fd == -1)
		return (-1);
	if (!s_temp)
	{
		if (!(s_temp = malloc(sizeof(char) * 1)))
			return (-1);
		s_temp[0] = '\0';
	}
	if ((l_index = ft_get_newline_index(s_temp)) != -1)
		return (ft_write_line_until_nl(&s_temp, line, l_index));
	while ((b_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[b_read] = '\0';
		if ((l_index = ft_get_newline_index(buff)) != -1)
			return (ft_buffer_in_line(buff, &s_temp, line));
		else
			s_temp = ft_add_buffer_in_content(buff, &s_temp);
	}
	return (get_after_read(b_read, &s_temp, buff, line));
}
