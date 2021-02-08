
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>

#include "get_next_line.h"
#include "libft.h"

typedef struct s_rgb
{
	int		r;
	int 	g;
	int		b;
}				t_rgb;

typedef struct	s_config
{
	int 	Rx;
	int		Ry;
	char	*NO_T;
	char	*SO_T;
	char	*WE_T;
	char	*EA_T;
	char	*S_T;

	t_rgb	*floor;
	t_rgb	*celling;

	char	**MAP;
}				t_config;
//typedef struct s_rgb
//{
//	int		F_R;
//	int 	F_G;
//	int		F_B;
//	int 	C_R;
//	int 	C_G;
//	int 	C_B;
//}				t_rgb;

void ft_print_st(t_config *map); 				//надо снести
int			get_next_line(int fd, char **line);
void		cub();
void ft_parse_map(t_config *config, char *line);
void ft_parse_data(t_config *config, char *line);
void parser_for_rgb_f(char *line, t_config *config, t_rgb *part_of_struct);

#endif