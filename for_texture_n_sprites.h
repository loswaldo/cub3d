/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_texture_n_sprites.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:14 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:20 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_FOR_TEXTURE_N_SPRITES_H
# define CUB_FOR_TEXTURE_N_SPRITES_H

# include "config.h"

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_double_coord
{
	double			x;
	double			y;
}					t_double_coord;

typedef struct		s_float_coord
{
	float		x;
	float		y;
}					t_float_coord;

typedef struct		s_for_sprites
{
	t_double_coord	sprite;
	t_double_coord	transform;
	t_coord			draw_start;
	t_coord			draw_end;
	t_coord			tex;
	t_coord			coord;

	int				sprite_sreen_x;
	int				sprite_height;
	int				sprite_width;
	int				stripe;

	double			inv_det;
}					t_for_sprites;

typedef struct		s_for_calculate
{
	t_float_coord	ray_dir;
	t_float_coord	side_dist;
	t_float_coord	delta_dist;

	float			perp_wall_dist;

	t_coord			map;
	t_coord			step_c;
	t_coord			tex;

	double			wall_x;
	double			step;
	double			tex_pos;

	int				side;
	int				draw_start;
	int				draw_end;
	int				line_height;
}					t_for_calculate;

void				calc_side_dist(t_for_calculate *value, t_config *config);
void				calculation(t_for_calculate *value, t_config *config,
								int x);
void				calc_perpl_wall_dist(t_config *config,
										t_for_calculate *value);
void				calc_draw_start_n_end(t_config *config,
											t_for_calculate *value);
void				check_side_n_tex_x_y(t_config *config,
										t_for_calculate *value);
void				fill_texture(t_config *config);
void				sprites_coord(t_config *config, t_sprites *sprite);
void				draw_map(t_config *config);
void				draw_sprites(t_config *config, float *z_buffer);
void				sprite_sorting(t_config *config, t_sprites *sp);

#endif
