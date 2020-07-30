/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:58:58 by user42            #+#    #+#             */
/*   Updated: 2020/07/16 18:59:02 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int				cut_line(char **reste, int back_n, char **line)
{
	char *temp;

	if (back_n < 0)
	{
		*line = ft_strdup(*reste);
		free(*reste);
		*reste = NULL;
		return (0);
	}
	*line = ft_substr(*reste, 0, back_n, 0);
	temp = ft_substr(*reste, back_n + 1, ft_strlen(*reste + back_n + 1), 0);
	free(*reste);
	*reste = temp;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char *reste[10240];
	int			ret;
	int			back_n;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buffer, 0) < 0 ||
			(!reste[fd] && !(reste[fd] = ft_stringnew(0))))
		return (-1);
	while ((back_n = ft_strichr(reste[fd], '\n')) < 0 &&
			(ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		reste[fd] = ft_strjoin(reste[fd], buffer, 1);
	}
	return (cut_line(&reste[fd], back_n, line));
}