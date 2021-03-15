/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:03 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub.h"
#include "parser.h"

void	error_output_n_exit(const char *str)
{
	int len;

	write(1, "Error\n", 6);
	len = ft_strlen(str);
	write(1, str, len);
	exit(1);
}

int		parse_digit(const char *line)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	i = ft_skip_spaces((char *)line, i);
	while (ft_isdigit(line[i]) && line[i] == '0')
		i++;
	while (ft_isdigit(line[i]))
	{
		num = (num * 10) + (line[i] - 48);
		if (num > 2147483647)
			return (20000);
		i++;
	}
	i = ft_skip_spaces((char *)line, i);
	if (!ft_isdigit(line[i]) && line[i])
		error_output_n_exit("WRONG SYMBOL");
	if (num > 2147483647)
		return (20000);
	return ((int)num);
}

void	check_line_rgb_again(char *line)
{
	int i;

	i = 1;
	i = ft_skip_spaces(line, i);
	i += skip_digits(line + i);
	i = ft_skip_spaces(line, i);
	if (line[i] == ',')
		i++;
	i = ft_skip_spaces(line, i);
	i += skip_digits(line + i);
	i = ft_skip_spaces(line, i);
	if (line[i] == ',')
		i++;
	i = ft_skip_spaces(line, i);
	i += skip_digits(line + i);
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]) && line[i])
		error_output_n_exit("WRONG NUMBER FOR COLOR");
}

void	free_color_array(char **str)
{
	char	**tmp;

	tmp = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(tmp);
}
