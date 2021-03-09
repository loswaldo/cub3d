#include "cub.h"

void draw_sprites(t_config *config, float * ZBuffer)
{
	//SPRITE CASTING
	//sort sprites from far to close
//	for(int i = 0; i < config->sp_quantity; i++)
//	{
//		spriteOrder[i] = i;
//		spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
//	}
//	sortSprites(spriteOrder, spriteDistance, config->sp_quantity);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < config->sp_quantity; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = config->sp[i].x - config->pl_pos_x;
		double spriteY = config->sp[i].y - config->pl_pos_y;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (config->plane_x * config->dir_y - config->dir_x * config->plane_y); //required for correct matrix multiplication

		double transformX = invDet * (config->dir_y * spriteX - config->dir_x * spriteY);
		double transformY = invDet * (-config->plane_y * spriteX + config->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((config->Rx / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(config->Ry / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + config->Ry / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + config->Ry / 2;
		if(drawEndY >= config->Ry) drawEndY = config->Ry - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (config->Ry / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= config->Rx) drawEndX = config->Rx - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * config->tmp_w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < config->Rx && transformY < ZBuffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - config->Ry * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * config->tmp_h) / spriteHeight) / 256;

					unsigned int color = my_mlx_pixel_take(&config->S_tex, texX, texY);
					if ((color & 0x00FFFFFF) != 0)
					{
						my_mlx_pixel_put(config->win, stripe, y, color);
					}

//					Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
//					if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}


