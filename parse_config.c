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
//	printf("Rx %d\n",map->Rx);
//	printf("Ry %d\n",map->Ry);
//	printf("SO_T %s\n",map->SO_T);
//	printf("EA_T%s\n",map->EA_T);
//	printf("WE_T%s\n",map->WE_T);
//	printf("NO_T%s\n",map->NO_T);
//	printf("S_T%s\n",map->S_T);
//	printf("c_r %d\n", map->celling->r);
//	printf("c_g %d\n", map->celling->g);
//	printf("c_b %d\n", map->celling->b);
//	printf("f_r %d\n", map->floor->r);
//	printf("f_g %d\n", map->floor->g);
//	printf("f_b %d\n", map->floor->b);
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
}
void parser_for_texture(char *line, char **part_of_struct, int i)
{
	*part_of_struct = ft_strdup(&line[i]);
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
//	printf("map = %s\n", config->MAP);
}

void ft_parse_data(t_config *config, char *line)
{
	int i;

	i = 0;
	i = ft_skip_spaces(line, i);
	if (line[i] == 'R')
	{
		parser_for_resolution(config, line);
	}
	if (line [i] == 'N' || line [i] == 'E' || line [i] == 'W' || line [i] == 'S')
	{
		if (line[i] == 'N')
		{
			if (!(config->NO_T))
			{
				parser_for_texture(line, &config->NO_T, 2);
			}
			else
			{
				printf("REITERATION TEXTURE");
				exit(1);
			}
		}
		if (line[i] == 'E')
		{
			if (!(config->EA_T))
			{
				parser_for_texture(line, &config->EA_T, 2);
			}
			else
			{
				printf("REITERATION TEXTURE");
				exit(1);
			}
		}
		if (line[i] == 'W')
		{
			if (!(config->WE_T))
			{
				parser_for_texture(line, &config->WE_T, 2);
			}
			else
			{
				printf("REITERATION TEXTURE");
				exit(1);
			}
		}
		if (line[i] == 'S' && line[i + 1] == 'O')
		{
			if (!(config->SO_T))
			{
				parser_for_texture(line, &config->SO_T, 2);
			}
			else
			{
				printf("REITERATION TEXTURE");
				exit(1);
			}
		}
		else if (line[i] == 'S')
		{
			if (!(config->S_T))
			{
				parser_for_texture(line, &config->S_T, 1);
			}
			else
			{
				printf("REITERATION TEXTURE");
				exit(1);
			}
		}
	}
	if (line[i] == 'F' || line[i] == 'C')
	{

		if (line[i] == 'F')
		{
			parser_for_rgb_f(line, config, config->floor);
		}
		if (line[i] == 'C')
		{
			parser_for_rgb_f(line, config, config->celling);
		}
	}
}