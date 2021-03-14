/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:11 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "parser.h"

void	check_line_for_rgb(char *line)
{
	int				i;
	int				count;
	const char		*error = "WRONG COLOR";

	i = 1;
	count = 0;
	i = ft_skip_spaces(line, i);
	while (line[i])
	{
		i += skip_digits(line + i);
		i = ft_skip_spaces(line, i);
		if (line[i] == ',')
		{
			count++;
			i++;
		}
		i = ft_skip_spaces(line, i);
		if (!ft_isdigit(line[i]) && line[i])
			error_output_n_exit(error);
	}
	if (count > 2)
		error_output_n_exit(error);
}

int		skip_digits(const char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
	{
		++i;
	}
	return (i);
}

int		is_valid_color(int color)
{
	return (color <= 255 && color >= 0);
}

int		parser_for_color(t_rgb *color_in_struct, const char *line)
{
	const char	*color_error = "WRONG COLOR";
	char		**color;

	color = ft_split(line, ',');
	if (color_in_struct->r == -1)
		color_in_struct->r = parse_digit(color[0]);
	else
		error_output_n_exit("REITERATION COLOR");
	if (color_in_struct->g == -1)
		color_in_struct->g = parse_digit(color[1]);
	else
		error_output_n_exit("REITERATION COLOR");
	if (color_in_struct->b == -1)
	color_in_struct->b = parse_digit(color[2]);
	else
		error_output_n_exit("REITERATION COLOR");
	if (!is_valid_color(color_in_struct->r) ||
		!is_valid_color(color_in_struct->g) ||
		!is_valid_color(color_in_struct->b))
		error_output_n_exit(color_error);
	return (skip_digits(line));
}

void	parser_for_rgb(char *line, t_rgb *part_of_struct)
{
	int		i;

	i = 1;
	check_line_for_rgb(line);
	check_line_rgb_again(line);
	i = ft_skip_spaces(line, i);
	parser_for_color(part_of_struct, line + i);
}
