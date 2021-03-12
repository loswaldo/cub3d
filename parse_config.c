/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:09 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_data_filled(t_config *config)
{
	return (config->floor->r != -1 && config->floor->g != -1
			&& config->floor->b != -1 && config->celling->r != -1
			&& config->celling->g != -1 && config->celling->b != -1
			&& config->no_t != NULL && config->we_t != NULL
			&& config->ea_t != NULL && config->so_t != NULL
			&& config->s_t != NULL && config->ry != 0
			&& config->rx != 0);
}

int		ft_skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	parser_for_resolution(t_config *config, char *line)
{
	int i;

	i = 1;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
		config->rx = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
		config->ry = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		error_output_n_exit("WRONG NUMBER FOR RESOLUTION");
	}
}

void	parser_for_texture(char *line, char **part_of_struct, int i)
{
	if (!(*part_of_struct))
		*part_of_struct = ft_strdup(&line[i + 1]);
	else
	{
		error_output_n_exit("REITERATION TEXTURE");
	}
}

void	ft_parse_map(t_config *config, char *line)
{
	char *tmp;

	if (config->map_width < (int)ft_strlen(line))
		config->map_width = ft_strlen(line);
	if (!(config->pre_map))
		config->pre_map = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(config->pre_map, "\n");
		free(config->pre_map);
		config->pre_map = ft_strjoin(tmp, line);
		free(tmp);
	}
}
