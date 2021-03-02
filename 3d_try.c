#include "cub.h"

//#define screenWidth 640
//#define screenHeight 480
#define texWidth 64
#define texHeight 64
//#define mapWidth 24
//#define mapHeight 24



//int karlic(t_for_win *win, t_config *config)
//{
//	double posX = config->pl_pos_y;
//	double posY = config->pl_pos_x;
//

//
//	double time = 0;
//	double oldTime = 0;
//
//		int x;
//		int w;
//		int h;

	void	draw_map(t_config *config, t_for_win *win)
	{
		double dir_x = 0;
		double dir_y = 1;
		double plane_x = 0.66;
		double plane_y = 0;
		//for (int x = 0; x < config->Rx; x++)
		int x;
		int y;

		x = 0;
		while (x < config->Rx)
		{
			//calculate ray position and direction
			float cameraX = 2 * x / (float)config->Rx - 1; //x-coordinate in camera space
			float rayDirX = dir_x + plane_x * cameraX;
			float rayDirY = dir_y + plane_y * cameraX;
			//which box of the map we're in
			int mapX = (int)(config->pl_pos_x);
			int mapY = (int)(config->pl_pos_y);

			//length of ray from current position to next x or y-side
			float sideDistX;
			float sideDistY;

			//length of ray from one x or y-side to next x or y-side
			float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			float perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
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
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
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

				// Check if ray has hit a wall
				if (config->MAP[mapX][mapY] == '1')
					hit = 1;
			}

			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - config->pl_pos_x + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - config->pl_pos_y + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(config->Ry / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + config->Ry / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + config->Ry / 2;
			if (drawEnd >= config->Ry)
				drawEnd = config->Ry - 1;

			double wallX; //where exactly the wall was hit
			if(side == 0)
				wallX = config->pl_pos_y + perpWallDist * rayDirY;
			else
				wallX = config->pl_pos_y + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			//x coordinate on the texture
			int texX = (int)(wallX * (double)(texWidth));
			if(side == 0 && rayDirX > 0)
				texX = texWidth - texX - 1;
			if(side == 1 && rayDirY < 0)
				texX = texWidth - texX - 1;

			// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - config->Ry / 2 + lineHeight / 2) * step;
			y = 0;
			unsigned int color;
			while (y < drawEnd)
			{
				if (y >= drawStart && y <= drawEnd)
				{
					int texY = (int)texPos & (texHeight - 1);
					texPos += step;

					if (side == 0)
					{
						if (stepX > 0)
						{
//							color = my_mlx_pixel_take(&map->north_texture, texX, texY);
//							my_mlx_pixel_put(&map->img, x, y, color);
							my_mlx_pixel_put(&win->img, x, y, 0xFF2FFF);
						}
						else if (stepX < 0)
						{
//							color = my_mlx_pixel_take(&win->south_texture, texX, texY);
//							my_mlx_pixel_put(&win->win, x, y, color);
							my_mlx_pixel_put(&win->img, x, y, 0xFFF9FF);
						}


					}
					if (side == 1)
					{
						if (stepY > 0)
						{
//							color = my_mlx_pixel_take(&win->west_texture, texX, texY);
//							my_mlx_pixel_put(&win->img, x, y, color);
							my_mlx_pixel_put(&win->img, x, y, 0xFFFFFF);
						}
						else if (stepY < 0)
						{
//							color = my_mlx_pixel_take(&win->east_texture, texX, texY);
//							my_mlx_pixel_put(&win->img, x, y, color);
							my_mlx_pixel_put(&win->img, x, y, 0x0000FF);
						}
					}
				}
				y++;
			}
			x++;
		}
	}
void print_blyat(t_for_win *win, t_config *config)
{
	void    *mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, config->Rx, config->Ry, "Hello world!");
	win->img = mlx_new_image(mlx, config->Rx, config->Ry);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_len,
								  &win->endian);
//	karlic(win, config);
	draw_map(config, win);
	mlx_put_image_to_window(mlx, mlx_win, win->img, 0, 0);
	mlx_loop(mlx);
}