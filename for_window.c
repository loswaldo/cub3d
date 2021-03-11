/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:01 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void for_mlx_create(char *path, t_for_win *tex, t_for_win *win)
{
	tex->img = mlx_xpm_file_to_image(win->mlx, path, &tex->width,
				&tex->height);
	if (!(tex->img))
	{
		error_output_n_exit("NON VALID FILE");
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
				&tex->line_len, &tex->endian);
}

void	fill_texture(t_config *config)
{
	for_mlx_create(config->SO_T, &config->SO_tex, config->win);
	for_mlx_create(config->S_T, &config->S_tex, config->win);
	for_mlx_create(config->WE_T, &config->WE_tex, config->win);
	for_mlx_create(config->EA_T, &config->EA_tex, config->win);
	for_mlx_create(config->NO_T, &config->NO_tex, config->win);
}
