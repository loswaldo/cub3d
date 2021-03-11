/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:47:05 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_hook_move(int key, t_config *config)
{
	float	move_s;
	float	move_r;

	move_s = 0.2f;
	move_r = 0.2f;

	if (key == 13)
	{
		if (config->map[(int)(config->pl_pos_x
							  + config->dir_x * move_s)]
			[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->dir_x * move_s;
		if (config->map[(int)(config->pl_pos_x)][(int)(config->pl_pos_y
													   + config->dir_y * move_s)] == '0')
			config->pl_pos_y += config->dir_y * move_s;
	}
	if (key == 1)
	{
		if (config->map[(int)(config->pl_pos_x
							  - config->dir_x * move_s)]
			[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->dir_x * move_s;
		if (config->map[(int)(config->pl_pos_x)]
			[(int)(config->pl_pos_y
				   - config->dir_y * move_s)] == '0')
			config->pl_pos_y -= config->dir_y * move_s;
	}
	if (key == 0)
	{
		if (config->map[(int)(config->pl_pos_x)]
			[(int)(config->pl_pos_y
				   + config->dir_x * move_s)] == '0')
			config->pl_pos_y += config->dir_x * move_s;
		if (config->map[(int)(config->pl_pos_x
							  - config->dir_y * move_s)]
			[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->dir_y * move_s;
	}
	if (key == 2)
	{
		if (config->map[(int)(config->pl_pos_x)]
			[(int)(config->pl_pos_y
				   - config->dir_x * move_s)] == '0')
			config->pl_pos_y -= config->dir_x * move_s;
		if (config->map[(int)(config->pl_pos_x
							  + config->dir_y * move_s)]
			[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->dir_y * move_s;
	}
}

void	key_hook_rotation(int key, t_config *config)
{
	float	rot_s;
	float	o_dirx;
	float	o_planex;

	rot_s = (float)0.1;
	if (key == 124 || key == 123)
	{
		if (key == 123)
			rot_s *= -1;
		o_dirx = config->dir_x;
		config->dir_x = config->dir_x * cosf(-rot_s) - config->dir_y *
													   sinf(-rot_s);
		config->dir_y = o_dirx * sinf(-rot_s) + config->dir_y *
												cosf(-rot_s);
		o_planex = config->plane_x;
		config->plane_x = config->plane_x * cosf(-rot_s)
						  - config->plane_y * sinf(-rot_s);
		config->plane_y = o_planex * sinf(-rot_s) + config->plane_y
													* cosf(-rot_s);
	}
}

int		key_hook(int key, t_config *config)
{
	if (key == 13 || key == 0 || key == 2 || key == 1)
		key_hook_move(key, config);
	if (key == 124 || key == 123)
		key_hook_rotation(key, config);
	if (key == 53)
		exit(0);
	mlx_destroy_image(config->win->mlx, config->win->img);
	config->win->img = mlx_new_image(config->win->mlx, config->rx, config->ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp,
										  &config->win->line_len, &config->win->endian);
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win,
							config->win->img, 0, 0);
	return (1);
}
