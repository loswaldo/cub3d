
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>

#include "get_next_line.h"
#include "libft.h"


typedef struct	s_config
{
	int 	Rx;
	int		Ry;
	char	*NO_T;
	char	*SO_T;
	char	*WE_T;
	char	*EA_T;
	char	*S_T;
	char 	*F_RGB;
	char 	*C_RGB;
	char	**MAP;
}				t_config;

int			get_next_line(int fd, char **line);
void		cub();

#endif