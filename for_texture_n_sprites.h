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
#define CUB_FOR_TEXTURE_N_SPRITES_H

#include "config.h"

typedef struct s_coord
{
	int x;
	int y;
	double dx;
	double dy;
	float	fx;
	float 	fy;
}				t_coord;

typedef struct s_for_sprites
{
	t_coord		sprite;
	t_coord		transform;
	t_coord		draw_start;
	t_coord 	draw_end;
	t_coord		tex;
	t_coord		coord;

	int 		sprite_sreen_x;
	int			sprite_height;
	int 		sprite_width;
	int 		stripe;


	double 		inv_det;



}				t_for_sprites;

typedef struct s_for_calculate
{
	float ray_dir_x;
	float ray_dir_y;
	float side_dist_x;
	float side_dist_y;
	int map_x;			/*todo: change to t_coord */
	int map_y;
	float delta_dist_x;
	float delta_dist_y;
	float perp_wall_dist;
	int step_x;
	int step_y;
	int side;
	double wall_x;
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;
	int draw_start;
	int draw_end;
	int line_height;
	unsigned int color;

}			t_for_calculate;


void	calc_side_dist(t_for_calculate *value, t_config *config);
void	calculation(t_for_calculate *value, t_config *config, int x);
void	calc_perpl_wall_dist(t_config *config, t_for_calculate *value);
void	calc_draw_start_n_end(t_config *config, t_for_calculate *value, int x);
void	check_side_n_tex_x_y(t_config *config, t_for_calculate *value);
void fill_texture(t_config *config);
void sprites_coord(t_config *config, t_sprites *sprite);
void	draw_map(t_config *config);
void draw_sprites(t_config *config, float *ZBuffer);

#endif
