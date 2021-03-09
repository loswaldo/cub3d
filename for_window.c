#include "cub.h"

void	my_mlx_pixel_put(t_for_win *data, int x, int y, unsigned int color)
{
	char	*dst;

	if ((x <= 1920 && x >= 0) || (y <= 1080 && y >= 0))
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void	key_hook_move(int key, t_config *config)
{
	float	move_s;
	float	move_r;
	
	move_s = 0.2f;
	move_r = 0.2f;
	printf("key = %d\n", key);
	if (key == 13) // up
	{
		if (config->MAP[(int)(config->pl_pos_x
					+ config->dir_x * move_s)]
						[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->dir_x * move_s;
		if (config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y
					+ config->dir_y * move_s)] == '0')
			config->pl_pos_y += config->dir_y * move_s;
	}
	if (key == 1) // down
	{
		if (config->MAP[(int)(config->pl_pos_x
					- config->dir_x * move_s)]
						[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->dir_x * move_s;
		if (config->MAP[(int)(config->pl_pos_x)]
				[(int)(config->pl_pos_y
					- config->dir_y * move_s)] == '0')
			config->pl_pos_y -= config->dir_y * move_s;
	}
	if (key == 0) // left
	{
		if (config->MAP[(int)(config->pl_pos_x)]
				[(int)(config->pl_pos_y
					+ config->dir_x * move_s)] == '0')
			config->pl_pos_y += config->dir_x * move_s;
		if (config->MAP[(int)(config->pl_pos_x
					- config->dir_y * move_s)]
						[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->dir_y * move_s;
	}
	if (key == 2) // right
	{
		if (config->MAP[(int)(config->pl_pos_x)]
				[(int)(config->pl_pos_y
					- config->dir_x * move_s)] == '0')
			config->pl_pos_y -= config->dir_x * move_s;
		if (config->MAP[(int)(config->pl_pos_x
					+ config->dir_y * move_s)]
						[(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->dir_y * move_s;
	}
	
	
	// float	c;

	// c = 1;
	// move_s = (float)0.2;
	// if (key == 1 || key == 0)
	// 	c = -1;
	// if (key == 13 || key == 1)
	// {
	// 	if (config->MAP[(int)(config->pl_pos_x - config->dir_x * move_s)]
	// 	[(int)(config->pl_pos_y)] == '0')
	// 		config->pl_pos_x += (config->dir_x * move_s * c);
	// 	if (config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y +
	// 	(c * config->dir_y * move_s))] == '0')
	// 		config->pl_pos_y += (config->dir_y * move_s * c);
	// }
	// if (key == 0 || key == 2)
	// {
	// 	if (config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y
	// 	+ config->dir_x * move_s)] == '0')
	// 		config->pl_pos_y -= (c * config->dir_x * move_s);
	// 	if (config->MAP[(int)(config->pl_pos_x + (c * config->dir_y *
	// 	move_s))][(int)(config->pl_pos_y)] == '0')
	// 		config->pl_pos_x += (c * config->dir_y * move_s);
	// }
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
		exit(1);
	mlx_destroy_image(config->win->mlx, config->win->img);
	config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp,
						&config->win->line_len, &config->win->endian);
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win,
							config->win->img, 0, 0);
	return (1);
}

void	fill_texture(t_config *config)
{
	config->NO_tex.img = mlx_xpm_file_to_image(config->win->mlx,
		config->NO_T, &config->NO_tex.width, &config->NO_tex.height);
	config->NO_tex.addr = mlx_get_data_addr(config->NO_tex.img,
		&config->NO_tex.bpp, &config->NO_tex.line_len, &config->NO_tex.endian);
	config->SO_tex.img = mlx_xpm_file_to_image(config->win->mlx,
		config->SO_T, &config->SO_tex.width, &config->SO_tex.height);
	config->SO_tex.addr = mlx_get_data_addr(config->SO_tex.img,
		&config->SO_tex.bpp, &config->SO_tex.line_len, &config->SO_tex.endian);
	config->EA_tex.img = mlx_xpm_file_to_image(config->win->mlx, config->EA_T,
		&config->EA_tex.width, &config->EA_tex.height);
	config->EA_tex.addr = mlx_get_data_addr(config->EA_tex.img,
		&config->EA_tex.bpp, &config->EA_tex.line_len, &config->EA_tex.endian);
	config->WE_tex.img = mlx_xpm_file_to_image(config->win->mlx, config->WE_T,
		&config->WE_tex.width, &config->WE_tex.height);
	config->WE_tex.addr = mlx_get_data_addr(config->WE_tex.img,
		&config->WE_tex.bpp, &config->WE_tex.line_len, &config->WE_tex.endian);

	config->S_tex.img = mlx_xpm_file_to_image(config->win->mlx, config->S_T, &config->S_tex.width, &config->S_tex.height);
	config->S_tex.addr = mlx_get_data_addr(config->S_tex.img, &config->S_tex.bpp, &config->S_tex.line_len, &config->S_tex.endian);
}
