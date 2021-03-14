/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:46:49 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:47:18 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "for_texture_n_sprites.h"

void	calc_side_dist(t_for_calculate *value, t_config *config)
{
	if (value->ray_dir.x < 0 && (value->step_c.x = -1))
	{
		value->side_dist.x = (config->pl_pos_x - value->map.x)
							* value->delta_dist.x;
	}
	else if ((value->step_c.x = 1))
	{
		value->side_dist.x = (value->map.x + 1.f - config->pl_pos_x)
							* value->delta_dist.x;
	}
	if (value->ray_dir.y < 0 && (value->step_c.y = -1))
	{
		value->side_dist.y = (config->pl_pos_y - value->map.y)
							* value->delta_dist.y;
	}
	else if ((value->step_c.y = 1))
	{
		value->side_dist.y = (value->map.y + 1.f - config->pl_pos_y)
							* value->delta_dist.y;
	}
}

void	calculation(t_for_calculate *value, t_config *config, int x)
{
	float camera_x;

	camera_x = 2 * x / (float)config->rx - 1;
	value->ray_dir.x = config->dir_x + config->plane_x * camera_x;
	value->ray_dir.y = config->dir_y + config->plane_y * camera_x;
	value->map.x = (int)(config->pl_pos_x);
	value->map.y = (int)(config->pl_pos_y);
	value->delta_dist.x = sqrtf(1 + (value->ray_dir.y * value->ray_dir.y)
									/ (value->ray_dir.x * value->ray_dir.x));
	value->delta_dist.y = sqrtf(1 + (value->ray_dir.x * value->ray_dir.x)
									/ (value->ray_dir.y * value->ray_dir.y));
}

void	calc_perpl_wall_dist(t_config *config, t_for_calculate *value)
{
	if (value->side == 0)
	{
		value->perp_wall_dist = (value->map.x - config->pl_pos_x +
								(1.f - value->step_c.x) / 2) / value->ray_dir.x;
	}
	else
	{
		value->perp_wall_dist = (value->map.y - config->pl_pos_y +
								(1.f - value->step_c.y) / 2) / value->ray_dir.y;
	}
}

void	calc_draw_start_n_end(t_config *config, t_for_calculate *value)
{
	calc_perpl_wall_dist(config, value);
	value->line_height = (int)(config->ry / value->perp_wall_dist);
	value->draw_start = -value->line_height / 2 + config->ry / 2;
	if (value->draw_start < 0)
		value->draw_start = 0;
	value->draw_end = value->line_height / 2 + config->ry / 2;
	if (value->draw_end >= config->ry)
		value->draw_end = config->ry - 1;
	if (value->side == 0)
	{
		value->wall_x = config->pl_pos_y + value->perp_wall_dist *
										value->ray_dir.y;
	}
	else
	{
		value->wall_x = config->pl_pos_x + value->perp_wall_dist *
										value->ray_dir.x;
	}
	value->wall_x -= floor((value->wall_x));
}

void	check_side_n_tex_x_y(t_config *config, t_for_calculate *value)
{
	if (value->side == 0)
	{
		config->tmp_w = value->step_c.x > 0 ? config->no_tex.width :
						config->so_tex.width;
		config->tmp_h = value->step_c.x > 0 ? config->no_tex.height :
						config->so_tex.height;
	}
	if (value->side == 1)
	{
		config->tmp_w = value->step_c.y > 0 ? config->we_tex.width :
						config->ea_tex.width;
		config->tmp_h = value->step_c.y > 0 ? config->we_tex.height :
						config->ea_tex.height;
	}
	value->tex.x = (int)(value->wall_x * (double)(config->tmp_w));
	if (value->side == 0 && value->ray_dir.x > 0)
		value->tex.x = config->tmp_w - value->tex.x - 1;
	if (value->side == 1 && value->ray_dir.y < 0)
		value->tex.x = config->tmp_w - value->tex.x - 1;
	value->step = 1.0 * config->tmp_h / value->line_height;
	value->tex_pos = (value->draw_start - config->ry
						/ 2 + value->line_height / 2) * value->step;
}
