#include "cub.h"


typedef struct s_for_win {
	void		*img;
	char 		*addr;
	int 		bpp;
	int 		line_len;
	int			endian;
}				t_for_win;

void            my_mlx_pixel_put(t_for_win *data, int x, int y, int color)
{
	char    *dst;


	if ((x <= 1920 && x >= 0) || (y <= 1080 && y >= 0))
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}
void print_map(t_config *config, t_for_win *win)
{
	int x;
	int y;
	int count_x;
	int count_y;

	x = 0;
	y = 0;
	count_x = 0;
	count_y = 0;


	while (config->MAP[y])
	{
		x = 0;
		while (config->MAP[y][x])
		{
			if (config->MAP[y][x] == '1')
			{
				count_y = 0;
				while (count_y <= 10)
				{
					count_x = 0;
					while (count_x <= 10)
					{
						my_mlx_pixel_put(win, ((x + 1) * 10) + count_x, ((y + 1) * 10) + count_y, 0x3e59c7);
						count_x++;
					}
					count_y++;
				}
			}
			if (config->MAP[y][x] == '0')
			{
				count_y = 0;
				while (count_y <= 10)
				{
					count_x = 0;
					while (count_x <= 10)
					{
						my_mlx_pixel_put(win, ((x + 1) * 10) + count_x, ((y + 1) * 10) + count_y, 0x9d33d6);
						count_x++;
					}
					count_y++;
				}

			}
			if (config->MAP[y][x] == '2')
			{
				count_y = 0;
				while (count_y <= 10)
				{
					count_x = 0;
					while (count_x <= 10)
					{
						my_mlx_pixel_put(win, ((x + 1) * 10) + count_x, ((y + 1) * 10) + count_y, 0x3fe877);
						count_x++;
					}
					count_y++;
				}
			}
			if (config->MAP[y][x] == 'N')
			{
				count_y = 0;
				while (count_y <= 10)
				{
					count_x = 0;
					while (count_x <= 10)
					{
						my_mlx_pixel_put(win, ((x + 1) * 10) + count_x, ((y + 1) * 10) + count_y, 0xe8853f);
						count_x++;
					}
					count_y++;
				}
			}

			x++;
		}
		y++;
	}
}
void for_window(t_config *config)
{
	void    *mlx;
	t_for_win win;
	void	*mlx_win;
//	int x = 1;
//	int y = 1;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	win.img = mlx_new_image(mlx, 1920, 1080);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_len,
								 &win.endian);
	print_map(config, &win);
//	while (y <= 150)
//	{
//		x = 1;
//		while (x <= 150)
//		{
//			if (x != y && y/2 != x && y*2 != x)
//			{
//				my_mlx_pixel_put(&win, x, y, x%2 == 0 ? 0x00FF0000 : 0x3e59c7);
//
//			}
//
//			x++;
//		}
//		y++;
//	}
	mlx_put_image_to_window(mlx, mlx_win, win.img, 0, 0);
	mlx_loop(mlx);
}

