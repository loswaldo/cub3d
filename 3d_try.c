#include "cub.h"

#define texWidth 512
#define texHeight 512

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
			int mapX = (int)(config->pl_pos_x);
			int mapY = (int)(config->pl_pos_y);
			float sideDistX;
			float sideDistY;

			float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			float perpWallDist;
			int stepX;
			int stepY;
			int hit = 0;
			int side;
			if(rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (config->pl_pos_x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - config->pl_pos_x) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (config->pl_pos_y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - config->pl_pos_y) * deltaDistY;
			}
			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (config->MAP[mapX][mapY] == '1')
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - config->pl_pos_x + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - config->pl_pos_y + (1 - stepY) / 2) / rayDirY;
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
			int texX = (int)(wallX * (double)(texWidth));
			if(side == 0 && rayDirX > 0)
				texX = texWidth - texX - 1;
			if(side == 1 && rayDirY < 0)
				texX = texWidth - texX - 1;
			double step = 1.0 * texHeight / lineHeight;
			double texPos = (drawStart - config->Ry / 2 + lineHeight / 2) * step;
			y = 0;
			unsigned int color;
			while (y < drawEnd)
			{
				if (y < drawStart)
					my_mlx_pixel_put(&config->win->img, x, y, 0x6ce6df);
				if (y >= drawStart && y <= drawEnd)
				{
					int texY = (int)texPos & (texHeight - 1);
					texPos += step;

					if (side == 0)
					{
						if (stepX > 0)
						{
							color = my_mlx_pixel_take(&config->NO_texture, texX, texY);
							my_mlx_pixel_put(&config->win->img, x, y, color);
						}
						else if (stepX < 0)
						{
							color = my_mlx_pixel_take(&config->SO_texture, texX, texY);
							my_mlx_pixel_put(&config->win->img, x, y, color);
						}

					}
					if (side == 1)
					{
						if (stepY > 0)
						{
							color = my_mlx_pixel_take(&config->WE_texture, texX, texY);
							my_mlx_pixel_put(&config->win->img, x, y, color);
						}
						else if (stepY < 0)
						{
							color = my_mlx_pixel_take(&config->EA_texture, texX, texY);
							my_mlx_pixel_put(&config->win->img, x, y, color);
						}
					}
				}
				y++;
			}
			int kek = drawEnd;
			while (kek < config->Ry)         ////пол
				my_mlx_pixel_put(&config->win->img, x, kek++, 0xd16ce6);
			x++;
		}
	}

void print_blyat(t_config *config)
{
	config->win->mlx = mlx_init();
	fill_texture(config);
	config->win->mlx_win = mlx_new_window(config->win->mlx, config->Rx, config->Ry, "Hello world!");
	config->win->img = mlx_new_image(config->win->mlx, config->Rx, config->Ry);
	config->win->addr = mlx_get_data_addr(config->win->img, &config->win->bpp, &config->win->line_len,
								  &config->win->endian);
	init(config);
	draw_map(config);
	mlx_put_image_to_window(config->win->mlx, config->win->mlx_win, config->win->img, 0, 0);
	mlx_hook(config->win->mlx_win, 2, 1L<<0, key_hook, config);
	mlx_loop(config->win->mlx);
}