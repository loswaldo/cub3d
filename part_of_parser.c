/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:08 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_is_identifier(char *line, int i, t_config *config)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parser_for_texture(line, &config->no_t, 2);
	else if (line[i] == 'S' && (line[i + 1] == 'O' || line[i + 1] == ' '))
		parser_for_texture(line, line[i + 1] == 'O'
		? &config->so_t : &config->s_t, line[i + 1] == 'O' ? 2 : 1);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		parser_for_texture(line, &config->we_t, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		parser_for_texture(line, &config->ea_t, 2);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		parser_for_resolution(config, line);
	else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		parser_for_rgb(line, line[i] == 'F' ? config->floor : config->celling);
	else if (line[i] == '1' && check_data_filled(config))
		return (1);
	else
		error_output_n_exit("WRONG STRING OR NOT ");
	return (0);
}

void	rgb_conversion(t_rgb *color, int *part_of_struct)
{
	if (color->r)
		*part_of_struct += color->r << 16;
	if (color->g)
		*part_of_struct += color->g << 8;
	if (color->b)
		*part_of_struct += color->b;
}

int		check_line(char *line, t_config *config)
{
	int		i;

	i = 0;
	if (line[i] == '\0')
	{
		if (check_data_filled(config) && config->pre_map)
			error_output_n_exit("map IS NOT map!");
		return (0);
	}
	i = ft_skip_spaces(line, i);
	if (line[i] == '\0')
		return (0);
	return (ft_is_identifier(line, i, config));
}

char	*ft_fill_spaces(char *str, int len)
{
	char	*b;
	int		i;

	i = 0;
	b = malloc(sizeof(char) * (len + 1));
	if (!b)
		return (0);
	while (str[i] != 0)
	{
		b[i] = str[i];
		i++;
	}
	while (i < len)
	{
		b[i] = ' ';
		i++;
	}
	b[i] = '\0';
	free(str);
	return (b);
}

int		map_symbol_check(char c, const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
