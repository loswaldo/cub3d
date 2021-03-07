#include "cub.h"


unsigned int		my_mlx_pixel_take(t_for_win *win, int x, int y)
{
	char	*dst;

	dst = win->addr + (y * win->line_len + x * (win->bpp / 8));
	return (*(unsigned int*)dst);
}
void init(t_config *config)
{
	config->dir_x = 0;
	config->dir_y = 1;
	config->plane_x = 0.66;
	config->plane_y = 0;
}

void put(t_config *config, int tex_x, int tex_y, int x, int y)
{
	unsigned int color;

	color = my_mlx_pixel_take(&config->tmp_tex, tex_x, tex_y);
	my_mlx_pixel_put(&config->win->img, x, y, color);
}

	void	draw_map(t_config *config)
	{
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
				config->tmp_tex = stepX > 0 ? config->NO_tex : config->SO_tex;
			}
			if (side == 1)
			{
				config->tmp_tex = stepX > 0 ? config->WE_tex : config->EA_tex;
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
				if (y < drawStart)
					my_mlx_pixel_put(&config->win->img, x, y, 0x6ce6df);
				if (y >= drawStart && y <= drawEnd)
				{
					int texY = (int)texPos & (config->tmp_h - 1);
					texPos += step;
					put(config, texX, texY, x, y);
				}
				y++;
			}
			int kek = drawEnd;
			while (kek < config->Ry)         ////JENSKII пол
				my_mlx_pixel_put(&config->win->img, x, kek++, 0xd16ce6);
			x++;
		}
//	}
/*
void draw_huyaw(t_config *config)*/

	int i = 0;
	while (i < config->sp_quantity)
	{
//		double spriteX = sprite[spriteOrder[i]].x - config->pl_pos_x;
//		double spriteY = sprite[spriteOrder[i]].y - config->pl_pos_y;

		i++;
	}
}


void output(t_config *config)
{
	config->win->mlx = mlx_init();
	fill_texture(config);
	config->win->mlx_win = mlx_new_window(config->win->mlx, config->Rx, config->Ry, "Hello world!");
	config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len,
								  &config->win->endian);
	init(config);
	config->sp = malloc(config->sp_quantity * sizeof(t_sprites));
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
	mlx_hook(config->win->mlx_win, 2, 1L<<0, key_hook, config);
	mlx_loop(config->win->mlx);
}