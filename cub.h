
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "get_next_line.h"
#include "libft.h"
#include "minilibx_mms_20200219/mlx.h"

typedef struct s_rgb
{
	int		r;
	int 	g;
	int		b;
}				t_rgb;

typedef struct s_for_win {
	void		*img;
	char 		*addr;
	void    	*mlx;
	void		*mlx_win;
	int 		bpp;
	int 		line_len;
	int			endian;
	float 		dir_x;
	float 		dir_y;
	float 		plane_x;
	float 		plane_y;
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

	t_rgb	*floor;
	t_rgb	*celling;
	t_for_win	*win;

	char	*PRE_MAP;
	char 	**MAP;
	int		map_width;
	int 	map_height;
	float	pl_pos_x;
	float 	pl_pos_y;
}				t_config;



void ft_print_st(t_config *map); 				//надо снести
//int			get_next_line(int fd, char **line);
void		cub();
void ft_parse_map(t_config *config, char *line);
void parser_for_rgb(char *line, t_rgb *part_of_struct);
void rgb_conversion(t_rgb *color, int *part_of_struct);
int check_line(char *line, t_config *config);
int ft_skip_spaces(char *line, int i);
int ft_is_identifier(char *line, int i, t_config *config);
int check_data_filled(t_config *config);
void map_validation(t_config *config);
void parser_for_texture(char *line, char **part_of_struct, int i);
void parser_for_resolution(t_config *config, char *line);
void for_window(t_config *config);
void my_mlx_pixel_put(t_for_win *data, int x, int y, int color);
void print_blyat(t_config *config);
void	draw_map(t_config *config);
int key_hook(int key,t_config *config);

#endif