#include "cub.h"

void take_n_put_color(t_for_win *texture, t_for_calculate *value, t_coord coord,
					  t_for_win *win)
{
	const unsigned int color = my_mlx_pixel_take(texture, value->tex_x,
												 value->tex_y);

	my_mlx_pixel_put(win, coord.x, coord.y, color);
}

void  texture_draw(t_config *config, t_for_calculate *value, int x, int y)
{
	t_coord coord = (t_coord){.x=x, .y=y};

	if (value->side == 0)
	{
		if (value->step_x > 0)
			take_n_put_color(&config->NO_tex, value, coord, config->win);
		else
			take_n_put_color(&config->SO_tex, value, coord, config->win);
	}
	if (value->side == 1)
	{
		if (value->step_y > 0)
			take_n_put_color(&config->WE_tex, value, coord, config->win);
		else
			take_n_put_color(&config->EA_tex, value, coord, config->win);
	}
}

void  directly_draw(t_config *config, t_for_calculate *value, int x)
{
	int y;

	y = 0;
	while (y < value->draw_end)
	{
		if (y < value->draw_start)
			my_mlx_pixel_put(config->win, x, y, config->cel);
		if (y >= value->draw_start && y <= value->draw_end)
		{
			value->tex_y = (int)value->tex_pos & (config->tmp_h - 1);
			value->tex_pos += value->step;
			texture_draw(config, value, x, y);
		}
		y++;
	}
	int kek = value->draw_end;
	while (kek < config->Ry)
		my_mlx_pixel_put(config->win, x, kek++, config->fl);
}

void	check_hit(t_for_calculate *value, char **MAP)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (value->side_dist_x < value->side_dist_y)
		{
			value->side_dist_x += value->delta_dist_x;
			value->map_x += value->step_x;
			value->side = 0;
		}
		else
		{
			value->side_dist_y += value->delta_dist_y;
			value->map_y += value->step_y;
			value->side = 1;
		}
		if (MAP[value->map_x][value->map_y] == '1')
			hit = 1;
	}
}

void	draw_map(t_config *config)
{
	t_for_calculate value;

	ft_bzero(&value, sizeof(t_for_calculate));
	float *ZBuffer = ft_calloc(config->Rx, sizeof(double));
	if (!(ZBuffer))
		error_output_n_exit("MALLOC ERROR");
	int x;

	x = 0;
	while (x < config->Rx)
	{
		calculation(&value, config, x);
		calc_side_dist(&value, config);
		check_hit(&value, config->MAP);
		calc_draw_start_n_end(config, &value, x);
		check_side_n_tex_x_y(config, &value);
		directly_draw(config, &value, x);
		x++;
		ZBuffer[x] = value.perp_wall_dist;
	}
	draw_sprites(config, ZBuffer);
}
