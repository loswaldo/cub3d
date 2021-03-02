#include "cub.h"


//typedef struct s_for_win {
//	void		*img;
//	char 		*addr;
//	int 		bpp;
//	int 		line_len;
//	int			endian;
//}				t_for_win;

void            my_mlx_pixel_put(t_for_win *data, int x, int y, int color)
{
	char    *dst;

	if ((x <= 1920 && x >= 0) || (y <= 1080 && y >= 0))
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void part_of_print_map(t_for_win *win, int x, int y, int square_size, int color)
{

	int count_x;
	int count_y;

	count_y = 0;
	while (count_y <= square_size)
	{
		count_x = 0;
		while (count_x <= square_size)
		{
			my_mlx_pixel_put(win, ((x + 1) * square_size) + count_x, ((y + 1) * square_size) + count_y, color);
			count_x++;
		}
		count_y++;
	}
}
//void print_plr(t_config *config, t_for_win *win, int x, int y, int square_size)
//{
//	while (config->MAP[y])
//	{
//		x = 0;
//		while (config->MAP[y][x])
//		{
//			if (config->MAP[y][x] == 'N' || config->MAP[y][x] == 'E'
//			|| config->MAP[y][x] == 'W' || config->MAP[y][x] == 'S')
//				part_of_print_map(win, x, y, square_size, 0x89de3e);
//			x++;
//		}
//		y++;
//	}
//}
void print_map(t_config *config, t_for_win *win)
{
	int x;
	int y;
	static const int square_size = 30;

	y = 0;
	while (config->MAP[y])
	{
		x = 0;
		while (config->MAP[y][x])
		{
			if (config->MAP[y][x] == '1')
				part_of_print_map(win, x, y, square_size, 0x3e59c7);
			if (config->MAP[y][x] == '2')
				part_of_print_map(win, x, y, square_size, 0xeb71ca);
			if (config->MAP[y][x] == 'N' || config->MAP[y][x] == 'E'
			|| config->MAP[y][x] == 'W' || config->MAP[y][x] == 'S')
				part_of_print_map(win, x, y, square_size, 0x89de3e);
			x++;
		}
		y++;
	}
}
int key_hook(int key, t_config *config)
{
	float	moveSpeed;
	float	rotSpeed;
	float	oldDirX;
	float	oldPlaneX;

	moveSpeed = (float)0.2;
	rotSpeed = 0.1;

	printf("keycode: %d\n", key);
	printf("BEFORE\n");
	printf("PLR_X: %f\n", config->pl_pos_x);
	printf("PLR_Y: %f\n", config->pl_pos_y);
	printf("DIR_X: %f\n", config->win->dir_x);
	printf("DIR_Y: %f\n", config->win->dir_x);
	printf("PLANE_X: %f\n", config->win->plane_x);
	printf("PLANE_Y: %f\n", config->win->plane_y);
	if (key == 13)
	{
		if(config->MAP[(int)(config->pl_pos_x - config->win->dir_x * moveSpeed)][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->win->dir_x * moveSpeed;
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y + config->win->dir_y * moveSpeed)] == '0')
			config->pl_pos_y += config->win->dir_y * moveSpeed;
	}
	else if (key == 1)
	{
		if(config->MAP[(int)(config->pl_pos_x - config->win->dir_x * moveSpeed)][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->win->dir_x * moveSpeed;
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y - config->win->dir_y * moveSpeed)] == '0')
			config->pl_pos_y -= config->win->dir_y * moveSpeed;
	}
	else if (key == 0)
	{
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y + config->win->dir_x * moveSpeed)] == '0')
			config->pl_pos_y += config->win->dir_x * moveSpeed;
		if(config->MAP[(int)(config->pl_pos_x - config->win->dir_y * moveSpeed)][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x -= config->win->dir_y * moveSpeed;
	}
	else if (key == 2)
	{
		if(config->MAP[(int)(config->pl_pos_x)][(int)(config->pl_pos_y + config->win->dir_x * moveSpeed)] == '0')
			config->pl_pos_y -= config->win->dir_x * moveSpeed;
		if(config->MAP[(int)(config->pl_pos_x + config->win->dir_y * moveSpeed)][(int)(config->pl_pos_y)] == '0')
			config->pl_pos_x += config->win->dir_y * moveSpeed;
	}
	else if (key == 124)
	{
		oldDirX = config->win->dir_x;
		config->win->dir_x = config->win->dir_x * cos(-rotSpeed) - config->win->dir_y * sin(-rotSpeed);
		config->win->dir_y = oldDirX * sin(-rotSpeed) + config->win->dir_y * cos(-rotSpeed);
		oldPlaneX = config->win->plane_x;
		config->win->plane_x = config->win->plane_x * cos(-rotSpeed) - config->win->plane_y * sin(-rotSpeed);
		config->win->plane_y = oldPlaneX * sin(-rotSpeed) + config->win->plane_y * cos(-rotSpeed);
	}
	else if (key == 123)
	{
		oldDirX = config->win->dir_x;
		config->win->dir_x = config->win->dir_x * cos(rotSpeed) - config->win->dir_y * sin(rotSpeed);
		config->win->dir_y = oldDirX * sin(rotSpeed) + config->win->dir_y * cos(rotSpeed);
		oldPlaneX = config->win->plane_x;
		config->win->plane_x = config->win->plane_x * cos(rotSpeed) - config->win->plane_y * sin(rotSpeed);
		config->win->plane_y = oldPlaneX * sin(rotSpeed) + config->win->plane_y * cos(rotSpeed);
	}
	else if (key == 53)
	{
		exit(1);
	}
	printf("AFTER\n");
	printf("PLR_X: %f\n", config->pl_pos_x);
	printf("PLR_Y: %f\n", config->pl_pos_y);
	printf("DIR_X: %f\n", config->win->dir_x);
	printf("DIR_Y: %f\n", config->win->dir_x);
	printf("PLANE_X: %f\n", config->win->plane_x);
	printf("PLANE_Y: %f\n", config->win->plane_y);
	mlx_destroy_image(config->win->mlx, config->win->img);
	config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len, &config->win->endian);
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
	return (1);
}
void for_window(t_config *config)
{
	config->win = malloc(sizeof(t_for_win));
//	void    *mlx;
//	t_for_win win;
//	karlic(&win);
	print_blyat(config);
//	void	*mlx_win;
//
//	mlx = mlx_init();
//	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//	win.img = mlx_new_image(mlx, 1920, 1080);
//	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_len,
//								 &win.endian);
//	mlx_key_hook(mlx_win, key_hook, &win);
//	print_map(config, &win);
////	print_plr(config, &win);
//	mlx_put_image_to_window(mlx, mlx_win, win.img, 0, 0);
//	mlx_loop(mlx);
}

