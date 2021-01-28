/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <loswaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:52:58 by loswaldo          #+#    #+#             */
/*   Updated: 2020/12/12 20:02:00 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>

int get_next_line(int fd, char **line);
char	*ft_strjoinn(char *s1, char const *s2);
char	*ft_strchar(const char *s, int c);
char	*ft_strdupp(char *s1);

#endif