/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <loswaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:46:36 by loswaldo          #+#    #+#             */
/*   Updated: 2020/12/12 19:57:44 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_rem(char *remainder, char **line)
{
	char	*res;
	char *tmp;

	res = NULL;
	if (remainder)
	{
		if ((res = ft_strchar(remainder, '\n')))
		{
			*res = '\0';
			*line = ft_strdupp(remainder);
			tmp = ft_strdupp(++res);
			free(remainder);
			remainder = tmp;
			return (remainder);
		}
		else
		{
			*line = ft_strdupp(remainder);
			free(remainder);
		}
	}
	else
		*line = ft_strdupp("");
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf;
	char			*res;
	int				rd;

	buf = NULL;
	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	remainder = ft_rem(remainder, line);
	while (!remainder && (rd = read(fd, buf, BUFFER_SIZE)))
	{
		buf[rd] = '\0';
		if ((res = ft_strchar(buf, '\n'))) {
			*res = '\0';
			remainder = ft_strdupp(++res);
		}
		*line = ft_strjoinn(*line, buf);
	}
	free(buf);
	return (!rd ? 0 : 1);
}
