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

#include <stdlib.h>
#include "cub.h"
#include "for_texture_n_sprites.h"

void	calculate_for_sprites(t_config *config, t_for_sprites *value, int i)
{
	value->sprite.x = config->sp[i].x - config->pl_pos_x;
	value->sprite.y = config->sp[i].y - config->pl_pos_y;
	value->inv_det = 1.0 / (config->plane_x * config->dir_y - config->dir_x
			* config->plane_y);
	value->transform.x = value->inv_det * (config->dir_y * value->sprite.x
			- config->dir_x * value->sprite.y);
	value->transform.y = value->inv_det * (-config->plane_y * value->sprite.x
			+ config->plane_x * value->sprite.y);
	value->sprite_sreen_x = (int)((config->rx / 2) * (1 + value->transform.x
			/ value->transform.y));
	value->sprite_height = abs((int)(config->ry / (value->transform.y)));
	value->draw_start.y = -value->sprite_height / 2 + config->ry / 2;
	if (value->draw_start.y < 0)
		value->draw_start.y = 0;
	value->draw_end.y = value->sprite_height / 2 + config->ry / 2;
	if (value->draw_end.y >= config->ry)
		value->draw_end.y = config->ry - 1;
	value->sprite_width = abs((int)(config->rx / (value->transform.y)));
	value->draw_start.x = -value->sprite_width / 2 + value->sprite_sreen_x;
	if (value->draw_start.x < 0)
		value->draw_start.x = 0;
	value->draw_end.x = value->sprite_width / 2 + value->sprite_sreen_x;
	if (value->draw_end.x >= config->rx)
		value->draw_end.x = config->rx - 1;
	value->stripe = value->draw_start.x;
}

void	drawing_sprites(t_for_sprites *value, t_for_win *texture,
					t_config *config)
{
	int				d;
	unsigned int	color;

	d = (value->coord.y) * 256 - config->ry * 128 + value->sprite_height * 128;
	value->tex.y = ((d * texture->height) / value->sprite_height) / 256;
	color = my_mlx_pixel_take(texture, value->tex.x, value->tex.y);
	if ((color & 0x00FFFFFF) != 0)
	{
		my_mlx_pixel_put(config, value->stripe, value->coord.y, color);
	}
	value->coord.y++;
}

void	draw_sprites(t_config *config, float *z_buffer)
{
	t_for_sprites	value;
	int				i;

	i = 0;
	sprite_sorting(config, config->sp);
	while (i < config->sp_quantity)
	{
		calculate_for_sprites(config, &value, i);
		while (value.stripe <= value.draw_end.x)
		{
			value.tex.x = (int)(256 * (value.stripe - (-value.sprite_width / 2
						+ value.sprite_sreen_x)) * config->s_tex.width
						/ value.sprite_width) / 256;
			if (value.transform.y > 0 && value.stripe > 0 && value.stripe <
				config->rx && value.transform.y < z_buffer[value.stripe])
			{
				value.coord.y = value.draw_start.y;
				while (value.coord.y <= value.draw_end.y)
					drawing_sprites(&value, &config->s_tex, config);
			}
			value.stripe++;
		}
		i++;
	}
}
