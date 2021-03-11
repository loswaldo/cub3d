
#ifndef CUB_CONFIG_H
#define CUB_CONFIG_H

typedef struct s_rgb
{
	int		r;
	int 	g;
	int		b;
}				t_rgb;

typedef struct s_sprites
{
	double x;
	double y;
	double dist;
}				t_sprites;

typedef struct s_for_win
{
	void		*img;
	char 		*addr;
	void    	*mlx;
	void		*mlx_win;
	int 		bpp;
	int 		line_len;
	int			endian;
	int			width;
	int 		height;
}				t_for_win;

typedef struct	s_config
{
	int 	Rx;
	int		Ry;
	char	*NO_T;
	char	*SO_T;
	char	*WE_T;
	char	*EA_T;
	char	*S_T;
	int 	fl;
	int		cel;
	int 	tmp_w;
	int 	tmp_h;

	t_rgb	*floor;
	t_rgb	*celling;
	t_for_win	*win;
	t_for_win 	NO_tex;
	t_for_win 	SO_tex;
	t_for_win 	WE_tex;
	t_for_win 	EA_tex;
	t_for_win	S_tex;

	t_sprites 	*sp;
	t_for_win	tmp_tex;

	char	*PRE_MAP;
	char 	**MAP;
	int		map_width;
	int 	map_height;
	float	pl_pos_x;
	float 	pl_pos_y;
	float 	dir_x;
	float 	dir_y;
	float 	plane_x;
	float 	plane_y;
	int 	sp_quantity;
	double *wall_dist;

	char	direction;
}				t_config;

#endif
