#include "cub.h"
int ft_skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
	}
	return (i);
}
void ft_print_st(t_config *map)
{
	printf("Rx %d\n",map->Rx);
	printf("Ry %d\n",map->Ry);
	printf("SO_T %s\n",map->SO_T);
	printf("EA_T%s\n",map->EA_T);
	printf("WE_T%s\n",map->WE_T);
	printf("NO_T%s\n",map->NO_T);
	printf("S_T%s\n",map->S_T);
	printf("c_r %d\n", map->celling->r);
	printf("c_g %d\n", map->celling->g);
	printf("c_b %d\n", map->celling->b);
	printf("f_r %d\n", map->floor->r);
	printf("f_g %d\n", map->floor->g);
	printf("f_b %d\n", map->floor->b);
	printf("rgb_f %d\n", map->fl);
	printf("rgb_c %d\n", map->cel);
}
void parser_for_resolution(t_config *config, char *line)
{
	int i;

	i = 1;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		config->Rx = ft_atoi(&line[i]);
	}
	while (ft_isdigit(line[i]))
	{
		i++;
	}
	i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		config->Ry = ft_atoi(&line[i]);
	}
	while (ft_isdigit(line[i]))
	{
		i++;
	}
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		printf("WRONG NUMBER FOR RESOLUTION");
		exit (1);
	}
}
void parser_for_texture(char *line, char **part_of_struct, int i)
{
	if (!(*part_of_struct))
	{
		*part_of_struct = ft_strdup(&line[i]);
	}
	else
	{
		printf("REITERATION TEXTURE");
		exit(1);
	}
}

void ft_parse_map(t_config *config, char *line)
{
	char *tmp;

	if (config->map_width < (int)ft_strlen(line))
	{
		config->map_width = ft_strlen(line);
	}
	if (!(config->MAP))
	{
		config->MAP = ft_strdup(line);
	}
	else
	{
		tmp = ft_strjoin(config->MAP, "\n");
		free(config->MAP);
		config->MAP = ft_strjoin(tmp, line);
		free(tmp);
	}
}
