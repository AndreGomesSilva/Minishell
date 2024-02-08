/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:29:58 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/25 16:38:03 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_read(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = allocate_char(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		*(buff + read_bytes) = '\0';
		save = ft_strjoin_gnl(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_last_or_new_line(char *save_buffer)
{
	int		index;
	char	*line;
	int		index_2;

	index = 0;
	if (!*save_buffer)
		return (NULL);
	while (*(save_buffer + index) && *(save_buffer + index) != '\n')
		index++;
	line = allocate_char((index + 2));
	if (!line)
		return (NULL);
	index_2 = 0;
	while (index_2 <= index)
	{
		*(line + index_2) = *(save_buffer + index_2);
		index_2++;
	}
	*(line + index + 1) = '\0';
	return (line);
}

char	*rebuild_after_newline(char *save_buffer)
{
	int		index;
	int		len;
	char	*str;
	int		index_2;

	index = 0;
	while (*(save_buffer + index) != '\0' && *(save_buffer + index) != '\n')
		index++;
	if (*(save_buffer + index) == '\0')
	{
		free(save_buffer);
		return (NULL);
	}
	len = ft_strlen(save_buffer);
	str = allocate_char(len - index);
	if (!str)
		return (NULL);
	index_2 = 0;
	while (*(save_buffer + ++index))
		*(str + index_2++) = *(save_buffer + index);
	*(str + index_2) = '\0';
	free(save_buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save_buffer = get_read(fd, save_buffer);
	if (!save_buffer)
		return (NULL);
	line = get_last_or_new_line(save_buffer);
	save_buffer = rebuild_after_newline(save_buffer);
	return (line);
}
