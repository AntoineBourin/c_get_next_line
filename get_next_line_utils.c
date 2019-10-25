/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:02:37 by abourin           #+#    #+#             */
/*   Updated: 2019/10/25 16:29:45 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_or_free(char *str, int is_free, char **content)
{
	int		i;

	i = 0;
	if (is_free && content)
	{
		free(*content);
		return (0);
	}
	while (str[i])
		i++;
	return (i);
}

int		ft_get_newline_index(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strconcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!dest)
	{
		src[ft_strlen_or_free(src, 0, NULL)] = '\0';
		return (src);
	}
	while (dest[j])
		j++;
	while (src[i])
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}

int		ft_write_line(char **content, char *buffer, char **line)
{
	int		i;
	int		j;

	i = 0;
	while ((*content)[i])
	{
		(*line)[i] = (*content)[i];
		i++;
	}
	j = 0;
	while (buffer[j] && j < ft_get_newline_index(buffer))
	{
		(*line)[i] = buffer[j];
		i++;
		j++;
	}
	(*line)[i] = '\0';
	return (j);
}

int		get_after_read(int b_read, char **s_temp, char *buff, char **line)
{
	int		l_index;

	l_index = 0;
	if (b_read < 0)
		return (-1);
	buff[0] = '\0';
	if (b_read == 0 && ft_get_newline_index(*s_temp) == -1)
	{
		ft_buffer_in_line(buff, s_temp, line);
		free(*s_temp);
		*s_temp = NULL;
		return (0);
	}
	else if ((l_index = ft_get_newline_index(*s_temp)) != -1)
		return (ft_write_line_until_nl(s_temp, line, l_index));
	return (-1);
}
