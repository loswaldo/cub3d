#include "cub.h"

void            my_mlx_pixel_put(t_for_win *data, int x, int y, int color)
{
	char    *dst;

	if ((x <= 1920 && x >= 0) || (y <= 1080 && y >= 0))
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

int key_hook(int key, t_config *config)
{
	float	moveSpeed;
	float	rotSpeed;
	float	oldDirX;
	float	oldPlaneX;
	float c;

	c = 1;
	moveSpeed = (float)0.2;
	rotSpeed = (float)0.1;

if (key == 13 || key == 1)
	{
		if (key == 1)
			c = -1;
		if(config->MAP[(int)(config->pl_pos_x - config->dir_x * moveSpeed)][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += (config->dir_x * moveSpeed * c);
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y + (c * config->dir_y * moveSpeed))] == '0')
			config->pl_pos_y += (config->dir_y * moveSpeed * c);
	}
	if (key == 0 || key == 2)
	{
		if (key == 0)
			c = -1;
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y + config->dir_x * moveSpeed)] == '0')
			config->pl_pos_y -= (c * config->dir_x * moveSpeed);
		if(config->MAP[(int)(config->pl_pos_x + (c * config->dir_y * moveSpeed))][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += (c * config->dir_y * moveSpeed);
	}
	if (key == 124 || key == 123)
	{
		if (key == 123)
			rotSpeed *= -1;
		oldDirX = config->dir_x;
		config->dir_x = config->dir_x * cos(-rotSpeed) - config->dir_y * sin(-rotSpeed);
		config->dir_y = oldDirX * sin(-rotSpeed) + config->dir_y * cos(-rotSpeed);
		oldPlaneX = config->plane_x;
		config->plane_x = config->plane_x * cos(-rotSpeed) - config->plane_y * sin(-rotSpeed);
		config->plane_y = oldPlaneX * sin(-rotSpeed) + config->plane_y * cos(-rotSpeed);

	}
	if (key == 53)
	{
		exit(1);
	}
	mlx_destroy_image(config->win->mlx, config->win->img);
	config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len, &config->win->endian);
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
	return (1);
}
void fill_texture(t_config *config)
{

	config->NO_texture.img = mlx_xpm_file_to_image(config->win->mlx, config->NO_T,
							 &config->NO_texture.width,&config->NO_texture.height);
	config->NO_texture.addr = mlx_get_data_addr(config->NO_texture.img, &config->NO_texture.bpp,
											  &config->NO_texture.line_len, &config->NO_texture.endian);
	config->SO_texture.img = mlx_xpm_file_to_image(config->win->mlx, config->SO_T,
								&config->SO_texture.width,&config->SO_texture.height);
	config->SO_texture.addr = mlx_get_data_addr(config->SO_texture.img, &config->SO_texture.bpp,
												 &config->SO_texture.line_len, &config->SO_texture.endian);
	config->EA_texture.img = mlx_xpm_file_to_image(config->win->mlx, config->EA_T,
								&config->EA_texture.width,&config->EA_texture.height);
	config->EA_texture.addr = mlx_get_data_addr(config->EA_texture.img, &config->EA_texture.bpp,
												 &config->EA_texture.line_len, &config->EA_texture.endian);
	config->WE_texture.img = mlx_xpm_file_to_image(config->win->mlx, config->WE_T,
								&config->WE_texture.width,&config->WE_texture.height);
	config->WE_texture.addr = mlx_get_data_addr(config->WE_texture.img, &config->WE_texture.bpp,
												 &config->WE_texture.line_len, &config->WE_texture.endian);

}
void for_window(t_config *config)
{
	config->win = malloc(sizeof(t_for_win));
	print_blyat(config);
}

