#include "cub.h"

unsigned int		my_mlx_pixel_take(t_for_win *win, int x, int y)
{
	char	*dst;

	dst = win->addr + (y * win->line_len + x * (win->bpp / 8));
	return (*(unsigned int*)dst);
}

void init(t_config *config)
{
	if(config->direction == 'N')
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

/*void put(t_config *config, int tex_x, int tex_y, int x, int y)
{
	unsigned int color;

	color = my_mlx_pixel_take(&config->tmp_tex, tex_x, tex_y);
	my_mlx_pixel_put(&config->win->img, x, y, color);
}*/

void	draw_map(t_config *config)
{
	float *ZBuffer = ft_calloc(config->Rx, sizeof(double));
	/*todo : check malloc*/

	int x;
	int y;

	x = 0;
	while (x < config->Rx)
	{
		float cameraX = 2 * x / (float)config->Rx - 1;
		float rayDirX = config->dir_x + config->plane_x * cameraX;
		float rayDirY = config->dir_y + config->plane_y * cameraX;
		int map_x = (int)(config->pl_pos_x);
		int map_y = (int)(config->pl_pos_y);
		float sideDistX;
		float sideDistY;

		float deltaDistX = sqrtf(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		float deltaDistY = sqrtf(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		float perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if(rayDirX < 0 && (stepX = -1))
			sideDistX = (config->pl_pos_x - map_x) * deltaDistX;
		else if ((stepX = 1))
			sideDistX = (map_x + 1.0 - config->pl_pos_x) * deltaDistX;
		if(rayDirY < 0 && (stepY = -1))
			sideDistY = (config->pl_pos_y - map_y) * deltaDistY;
		else if ((stepY = 1))
			sideDistY = (map_y + 1.0 - config->pl_pos_y) * deltaDistY;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_y += stepY;
				side = 1;
			}
			if (config->MAP[map_x][map_y] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (map_x - config->pl_pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (map_y - config->pl_pos_y + (1 - stepY) / 2) / rayDirY;
		config->wall_dist[x] = perpWallDist;
		int lineHeight = (int)(config->Ry / perpWallDist);
		int drawStart = -lineHeight / 2 + config->Ry / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + config->Ry / 2;
		if (drawEnd >= config->Ry)
			drawEnd = config->Ry - 1;
		double wallX;
		if(side == 0)
			wallX = config->pl_pos_y + perpWallDist * rayDirY;
		else
			wallX = config->pl_pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		if (side == 0)
		{
			config->tmp_w = stepX > 0 ? config->NO_tex.width : config->SO_tex.width;
			config->tmp_h = stepX > 0 ? config->NO_tex.height : config->SO_tex.height;
			// config->tmp_tex = stepX > 0 ? config->NO_tex : config->SO_tex;
		}
		if (side == 1)
		{
			// config->tmp_tex = stepX > 0 ? config->WE_tex : config->EA_tex;
			config->tmp_w = stepX > 0 ? config->WE_tex.width : config->EA_tex.width;
			config->tmp_h = stepX > 0 ? config->WE_tex.height : config->EA_tex.height;
		}
		int texX = (int)(wallX * (double)(config->tmp_w));
		if(side == 0 && rayDirX > 0)
			texX = config->tmp_w - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = config->tmp_w - texX - 1;
		double step = 1.0 * config->tmp_h / lineHeight;
		double texPos = (drawStart - config->Ry / 2 + lineHeight / 2) * step;
		y = 0;
		while (y < drawEnd)
		{
			// write(1, "228", 3);
			if (y < drawStart)
				my_mlx_pixel_put(config->win, x, y, 0x6ce6df);
			if (y >= drawStart && y <= drawEnd)
			{
				int texY = (int)texPos & (config->tmp_h - 1);
				texPos += step;
				// put(config, texX, texY, x, y);
				unsigned int color;
				if (side == 0)
				{
					if (stepX > 0)
					{
						color = my_mlx_pixel_take(&config->NO_tex, texX, texY);
						my_mlx_pixel_put(config->win, x, y, color);
					}
					else if (stepX < 0)
					{
						color = my_mlx_pixel_take(&config->SO_tex, texX, texY);
						my_mlx_pixel_put(config->win, x, y, color);
					}


				}
				if (side == 1)
				{
					if (stepY > 0)
					{
						color = my_mlx_pixel_take(&config->WE_tex, texX, texY);
						my_mlx_pixel_put(config->win, x, y, color);
						//my_mlx_pixel_put(config->win, x, y, 0xFFFFFF);
					}
					else if (stepY < 0)
					{
						color = my_mlx_pixel_take(&config->EA_tex, texX, texY);
						my_mlx_pixel_put(config->win, x, y, color);
						//my_mlx_pixel_put(&map->img_win, x, y, 0x0000FF);
					}
				}
			}
			y++;
		}
		int kek = drawEnd;
		while (kek < config->Ry)         ////JENSKII пол
			my_mlx_pixel_put(config->win, x, kek++, 0xd16ce6);
		x++;

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}
	draw_sprites(config, ZBuffer);
}


static void		filling_file_screenshot(int fd, t_config *config)
{
	int	i;
	int	j;
	int	color;

	i = config->Ry;
	while (--i >= 0)
	{
		j = -1;
		while (++j < config->Rx)
		{
			color = *(int*)(config->win->addr + (i * config->win->line_len
					+ j * (config->win->bpp / 8)));
			write(fd, &color, 4);
		}
	}
}

void			continue_screenshot(t_config *config, int fd)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = config->Rx
		* config->Ry * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &config->Rx, 4);
	write(fd, &config->Ry, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void			screenshot(t_config *config)
{
	int fd;
	int size_screen;
	int zero;
	int size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	size_screen = config->Rx
		* config->Ry * 4 + 54;
	zero = 0;
	size = config->Rx
		* config->Ry;
	if (fd < 0)
		write(1, "Error\n", 6);
	continue_screenshot(config, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	filling_file_screenshot(fd, config);
	close(fd);
}

void output(t_config *config, int argc)
{
	if (argc == 3)
	{
		config->win->mlx = mlx_init();
		fill_texture(config);
		config->win->mlx_win = mlx_new_window(config->win->mlx, config->Rx, config->Ry, "Hello world!");
		config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
		config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len,
									  &config->win->endian);
		init(config);
//		config->sp = malloc(config->sp_quantity * sizeof(t_sprites));
		draw_map(config);
		mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
		screenshot(config);
	}
	else if (argc <= 3)
	{
		config->win->mlx = mlx_init();
		fill_texture(config);
		config->win->mlx_win = mlx_new_window(config->win->mlx, config->Rx, config->Ry, "Hello world!");
		config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
		config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len,
									  &config->win->endian);
		init(config);
//		config->sp = malloc(config->sp_quantity * sizeof(t_sprites));
		draw_map(config);
		mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
		mlx_hook(config->win->mlx_win, 2, 1L<<0, key_hook, config);
		mlx_loop(config->win->mlx);
	}
}