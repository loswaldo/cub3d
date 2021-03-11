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
			&& config->NO_T != NULL && config->WE_T != NULL && config->EA_T != NULL
			&& config->SO_T != NULL && config->S_T != NULL && config->Ry != 0
			&& config->Rx != 0);
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
		config->Rx = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
		config->Ry = ft_atoi(&line[i]);
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
	if (!(config->PRE_MAP))
		config->PRE_MAP = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(config->PRE_MAP, "\n");
		free(config->PRE_MAP);
		config->PRE_MAP = ft_strjoin(tmp, line);
		free(tmp);
	}
}
