/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:10 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:20 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_CONFIG_H
# define CUB_CONFIG_H

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_sprites
{
	double		x;
	double		y;
	double		dist;
}				t_sprites;

typedef struct	s_for_win
{
	void		*img;
	char		*addr;
	void		*mlx;
	void		*mlx_win;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_for_win;

typedef struct	s_config
{
	int			rx;
	int			ry;
	char		*no_t;
	char		*so_t;
	char		*we_t;
	char		*ea_t;
	char		*s_t;
	int			fl;
	int			cel;
	int			tmp_w;
	int			tmp_h;

	t_rgb		*floor;
	t_rgb		*celling;
	t_for_win	*win;
	t_for_win	no_tex;
	t_for_win	so_tex;
	t_for_win	we_tex;
	t_for_win	ea_tex;
	t_for_win	s_tex;

	t_sprites	*sp;

	char		*pre_map;
	char		**map;
	int			map_width;
	int			map_height;
	float		pl_pos_x;
	float		pl_pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	int			sp_quantity;

	char		direction;
}				t_config;

#endif
