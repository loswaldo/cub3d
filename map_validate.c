/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 03:30:21 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 03:30:31 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sprites_counter(t_config *config)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (config->pre_map[i])
	{
		if (config->pre_map[i] == '2')
		{
			count++;
		}
		i++;
	}
	config->sp_quantity = count;
}

void	part_of_map_checker(t_config *config, int x, int y)
{
	int		i;
	int		j;

	j = 0;
	x += -1;
	y += -1;
	if ((x < 0 || x >= config->map_width) || (y < 0 || y >= config->map_height))
		error_output_n_exit("map IS NOT VALID!");
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			if (!(map_symbol_check(config->map[y + j][x + i], "102NWES")))
				error_output_n_exit("map IS NOT VALID!!!!!!!");
			i++;
		}
		j++;
		if (y < 0 || y > config->map_height)
			error_output_n_exit("map IS NOT VALID!!!!!!!");
	}
}

void	find_player_position(t_config *config, int check)
{
	int x;
	int y;

	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (config->map[y][x] == 'S' || config->map[y][x] == 'N'
				|| config->map[y][x] == 'W' || config->map[y][x] == 'E')
			{
				check++;
				config->direction = config->map[y][x];
				config->map[y][x] = '0';
				config->pl_pos_y = (float)(x + 0.01);
				config->pl_pos_x = (float)(y + 0.01);
			}
			x++;
		}
		y++;
	}
	if (check != 1)
		error_output_n_exit("map ERROR(number of start position)");
}

void	map_checker(t_config *config)
{
	int		x;
	int		y;

	find_player_position(config, 0);
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (map_symbol_check(config->map[y][x], "02NWES"))
				part_of_map_checker(config, x, y);
			x++;
		}
		y++;
	}
}

void	map_validation(t_config *config)
{
	char	*tmp;
	int		y;

	y = 0;
	sprites_counter(config);
	tmp = config->pre_map;
	config->pre_map = ft_strtrim(config->pre_map, "\n");
	free(tmp);
	config->map = ft_split(config->pre_map, '\n');
	while (config->map[y])
	{
		if (config->map[y] != 0 && config->map_width >
			(int)ft_strlen(config->map[y]))
			config->map[y] = ft_fill_spaces(config->map[y], config->map_width);
		y++;
	}
	config->map_height = y - 1;
	free(config->pre_map);
	config->pre_map = NULL;
	map_checker(config);
}
