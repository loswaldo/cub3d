/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:16 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:20 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse(t_config *config, char *file_name)
{
	char	*line;
	int		ret;
	int		fd;

	ft_init_struct(config);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("FILE ERROR");
		exit(1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (check_line(line, config) && check_data_filled(config))
		{
			ft_parse_map(config, line);
		}
		free(line);
	}
	if (ret == -1)
	{
		error_output_n_exit("GNL ERROR");
	}
	ft_parse_map(config, line);
	free(line);
}

void	sprites_coord(t_config *config, t_sprites *sprite)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	while (config->map[y])
	{
		while (config->map[y][x])
		{
			if (config->map[y][x] == '2')
			{
				sprite[i].x = ((double)y + 0.5);
				sprite[i].y = ((double)x + 0.5);
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
