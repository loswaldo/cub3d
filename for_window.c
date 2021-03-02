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
int key_hook(int key/*, t_for_win *win*/)
{
	if (key == 13)
	{

	}
	if (key == 1)
	{

	}
	if (key == 0)
	{

	}
	if (key == 2)
	{

	}
	if (key == 53)
	{
//		exit(1);
	}
	return (0);
}
void for_window(t_config *config)
{
//	void    *mlx;
	t_for_win win;
//	karlic(&win);
	print_blyat(&win, config);
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

