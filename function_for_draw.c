/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_for_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:02 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	my_mlx_pixel_take(t_for_win *win, int x, int y)
{
	char	*dst;

	dst = win->addr + (y * win->line_len + x * (win->bpp / 8));
	return (*(unsigned int*)dst);
}

void			my_mlx_pixel_put(t_for_win *data, int x, int y,
								unsigned int color)
{
	char	*dst;

	if ((x <= 1920 && x >= 0) || (y <= 1080 && y >= 0))
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void			init(t_config *config)
{
	if (config->direction == 'N')
	{
		config->dir_x = -1;
		config->plane_y = 0.66f;
	}
	if (config->direction == 'W')
	{
		config->dir_y = -1;
		config->plane_x = -0.66f;
	}
	if (config->direction == 'E')
	{
		config->dir_y = 1;
		config->plane_x = 0.66f;
	}
	if (config->direction == 'S')
	{
		config->dir_x = 1;
		config->plane_y = -0.66f;
	}
}

void			output(t_config *config, int is_screenshot)
{
	config->win->mlx = mlx_init();
	fill_texture(config);
	if (!is_screenshot)
		config->win->mlx_win = mlx_new_window(config->win->mlx,
											  config->rx, config->ry, "Cute girls & cakes");
	config->win->img = mlx_new_image(config->win->mlx, config->rx, config->ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp,
								&config->win->line_len, &config->win->endian);
	init(config);
	draw_map(config);
	if (is_screenshot)
		screenshot(config);
	else
	{
		mlx_put_image_to_window(config->win->mlx, config->win->mlx_win,
								config->win->img, 0, 0);
		mlx_hook(config->win->mlx_win, 2, 1L << 0, key_hook, config);
		mlx_loop(config->win->mlx);
	}
}
