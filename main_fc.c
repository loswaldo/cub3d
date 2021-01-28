#include "cub.h"

void	ft_init(t_list *map)
{
	map->Rx = 0;
	map->Ry = 0;
	map->WE_T = NULL;
	map->SO_T = NULL;
	map->NO_T = NULL;
	map->EA_T = NULL;
	map->S_T = NULL;
	map->C_RGB = NULL;
	map->F_RGB = NULL;
	map->MAP = NULL;

}

void cub()
{
	t_list  map;
	ft_init(&map);
}