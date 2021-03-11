/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:48 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:53 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void swap(double *d1, double *d2)
{
	double tmp;

	tmp = *d2;
	*d2 = *d1;
	*d1 = tmp;
}

void swap_value(t_sprites *first, t_sprites *second)
{
	swap(&first->dist, &second->dist);
	swap(&first->x, &second->x);
	swap(&first->y, &second->y);
}

void sprite_sorting(t_config *config, t_sprites *sp)
{
	int i;
	int j;

	i = 0;
	while (i < config->sp_quantity)
	{
		sp[i].dist = ((config->pl_pos_x - sp[i].x) *
		(config->pl_pos_x - sp[i].x) + (config->pl_pos_y - sp[i].y) * (config->pl_pos_y - sp[i].y));
		i++;
	}
	i = 0;
	while (i < config->sp_quantity)
	{
		j = config->sp_quantity - 1;
		while(j > i)
		{
			if (sp[j - 1].dist < sp[j].dist)
			{
				swap_value(&sp[j-1], &sp[j]);
			}
			j--;
		}
		i++;
	}
}

void calculate_for_sprites(t_config *config, t_for_sprites *value, int i)
{
	value->sprite.dx = config->sp[i].x - config->pl_pos_x;
	value->sprite.dy = config->sp[i].y - config->pl_pos_y;
	value->inv_det = 1.0 / (config->plane_x * config->dir_y - config->dir_x * config->plane_y);
	value->transform.dx = value->inv_det * (config->dir_y * value->sprite.dx - config->dir_x * value->sprite.dy);
	value->transform.dy = value->inv_det * (-config->plane_y * value->sprite.dx + config->plane_x * value->sprite.dy);
	value->sprite_sreen_x = (int)((config->rx / 2) * (1 + value->transform.dx / value->transform.dy));
	value->sprite_height = abs((int)(config->ry / (value->transform.dy)));
	value->draw_start.y = -value->sprite_height / 2 + config->ry / 2;
	if(value->draw_start.y < 0) value->draw_start.y = 0;
	value->draw_end.y = value->sprite_height / 2 + config->ry / 2;
	if(value->draw_end.y >= config->ry) value->draw_end.y = config->ry - 1;
	value->sprite_width = abs( (int) (config->ry / (value->transform.dy)));
	value->draw_start.x = -value->sprite_width / 2 + value->sprite_sreen_x;
	if(value->draw_start.x < 0) value->draw_start.x = 0;
	value->draw_end.x = value->sprite_width / 2 + value->sprite_sreen_x;
	if(value->draw_end.x >= config->rx) value->draw_end.x = config->rx - 1;
}

void drawing_sprites(t_for_sprites *value, t_for_win *texture, t_config *config)
{
	int d = (value->coord.y) * 256 - config->ry * 128 + value->sprite_height * 128;
	value->tex.y = ((d * texture->height) / value->sprite_height) / 256;
	unsigned int color = my_mlx_pixel_take(texture, value->tex.x, value->tex.y);
	if ((color & 0x00FFFFFF) != 0)
	{
		my_mlx_pixel_put(config->win, value->stripe, value->coord.y, color);
	}
}

void draw_sprites(t_config *config, float * ZBuffer)
{
	t_for_sprites value;

	int i;

	i = 0;
	sprite_sorting(config, config->sp);
	while (i < config->sp_quantity)
	{
		calculate_for_sprites(config, &value, i);

		value.stripe = value.draw_start.x;

		while (value.stripe <= value.draw_end.x)
		{
			value.tex.x = (int)(256 * (value.stripe - (-value.sprite_width / 2 + value.sprite_sreen_x)) * config->s_tex.width / value.sprite_width) / 256;
			if (value.transform.dy > 0 && value.stripe > 0 && value.stripe < config->rx && value.transform.dy < ZBuffer[value.stripe])
			{
				value.coord.y = value.draw_start.y;
				while (value.coord.y <= value.draw_end.y)
				{
					drawing_sprites(&value, &config->s_tex, config);
					value.coord.y++;
				}
			}
			value.stripe++;
		}
		i++;
	}
}


