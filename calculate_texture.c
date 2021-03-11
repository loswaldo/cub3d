
#include "for_texture.h"
#include "cub.h"

void calc_side_dist(t_for_calculate *value, t_config *config)
{
	if(value->ray_dir_x < 0 && (value->step_x = -1))
	{
		value->side_dist_x = (config->pl_pos_x - value->map_x)
							 * value->delta_dist_x;
	}
	else if ((value->step_x = 1))
	{
		value->side_dist_x = (value->map_x + 1.0 - config->pl_pos_x)
							 * value->delta_dist_x;
	}
	if(value->ray_dir_y < 0 && (value->step_y = -1))
	{
		value->side_dist_y = (config->pl_pos_y - value->map_y)
							 * value->delta_dist_y;
	}
	else if ((value->step_y = 1))
	{
		value->side_dist_y = (value->map_y + 1.0 - config->pl_pos_y)
							 * value->delta_dist_y;
	}
}

void	calculation(t_for_calculate *value, t_config *config, int x)
{
	float camera_x;

	camera_x = 2 * x / (float)config->Rx - 1;
	value->ray_dir_x = config->dir_x + config->plane_x * camera_x;
	value->ray_dir_y = config->dir_y + config->plane_y * camera_x;
	value->map_x = (int)(config->pl_pos_x);
	value->map_y = (int)(config->pl_pos_y);
	value->delta_dist_x = sqrtf(1 + (value->ray_dir_y * value->ray_dir_y)
									/ (value->ray_dir_x * value->ray_dir_x));
	value->delta_dist_y = sqrtf(1 + (value->ray_dir_x * value->ray_dir_x)
									/ (value->ray_dir_y * value->ray_dir_y));
}

void	calc_perpl_wall_dist(t_config *config, t_for_calculate *value)
{
	if (value->side == 0)
	{
		value->perp_wall_dist = (value->map_x - config->pl_pos_x +
								 (1 - value->step_x) / 2) / value->ray_dir_x;
	}
	else
	{
		value->perp_wall_dist = (value->map_y - config->pl_pos_y +
								 (1 - value->step_y) / 2) / value->ray_dir_y;
	}
}

void	calc_draw_start_n_end(t_config *config, t_for_calculate *value, int x)
{
	calc_perpl_wall_dist(config, value);
	config->wall_dist[x] = value->perp_wall_dist;
	value->line_height = (int)(config->Ry / value->perp_wall_dist);
	value->draw_start = -value->line_height / 2 + config->Ry / 2;
	if (value->draw_start < 0)
		value->draw_start = 0;
	value->draw_end = value->line_height / 2 + config->Ry / 2;
	if (value->draw_end >= config->Ry)
		value->draw_end = config->Ry - 1;
	if(value->side == 0)
	{
		value->wall_x = config->pl_pos_y + value->perp_wall_dist *
										   value->ray_dir_y;
	}
	else
	{
		value->wall_x = config->pl_pos_x + value->perp_wall_dist *
										   value->ray_dir_x;
	}
	value->wall_x -= floor((value->wall_x));
}

void	check_side_n_tex_x_y(t_config *config, t_for_calculate *value)
{
	if (value->side == 0)
	{
		config->tmp_w = value->step_x > 0 ? config->NO_tex.width :
						config->SO_tex.width;
		config->tmp_h = value->step_x > 0 ? config->NO_tex.height :
						config->SO_tex.height;
	}
	if (value->side == 1)
	{
		config->tmp_w = value->step_x > 0 ? config->WE_tex.width :
						config->EA_tex.width;
		config->tmp_h = value->step_x > 0 ? config->WE_tex.height :
						config->EA_tex.height;
	}
	value->tex_x = (int)(value->wall_x * (double)(config->tmp_w));
	if(value->side == 0 && value->ray_dir_x > 0)
		value->tex_x = config->tmp_w - value->tex_x - 1;
	if(value->side == 1 && value->ray_dir_y < 0)
		value->tex_x = config->tmp_w - value->tex_x - 1;
	value->step = 1.0 * config->tmp_h / value->line_height;
	value->tex_pos = (value->draw_start - config->Ry
										  / 2 + value->line_height / 2) * value->step;
}
