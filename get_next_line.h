/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:02:45 by abourin           #+#    #+#             */
/*   Updated: 2019/10/25 16:16:20 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		ft_strlen_or_free(char *str, int free, char **content);
int		ft_get_newline_index(char *str);
char	*ft_strconcat(char *dest, char *src);
char	*ft_add_buffer_in_content(char *buffer, char **content);
void	ft_set_buffer_end_in_content(char *buffer, char **content,
					int buff_len, int nl_index);
int		ft_buffer_in_line(char *buffer, char **content, char **line);
int		ft_write_line_until_nl(char **content, char **line, int l_index);
int		ft_write_line(char **content, char *buffer, char **line);
int		get_after_read(int b_read, char **s_temp, char *buff, char **line);

#endif
