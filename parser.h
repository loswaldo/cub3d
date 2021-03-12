/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:45 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:53 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_H
# define CUB_PARSER_H

# include "config.h"

void	ft_parse_map(t_config *config, char *line);
void	parser_for_rgb(char *line, t_rgb *part_of_struct);
void	parser_for_texture(char *line, char **part_of_struct, int i);
void	parser_for_resolution(t_config *config, char *line);
void	parse(t_config *config, char *file_name);

void	rgb_conversion(t_rgb *color, int *part_of_struct);
int		check_line(char *line, t_config *config);
int		ft_skip_spaces(char *line, int i);
int		ft_is_identifier(char *line, int i, t_config *config);
int		check_data_filled(t_config *config);
void	map_validation(t_config *config);
int		map_symbol_check(char c, const char *str);
char	*ft_fill_spaces(char *str, int len);

#endif
