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
//	printf("%d\n",map->Rx);
//	printf("%d\n",map->Ry);
	printf("SO_T %s\n",map->SO_T);
	printf("EA_T%s\n",map->EA_T);
	printf("WE_T%s\n",map->WE_T);
	printf("NO_T%s\n",map->NO_T);
//	printf("%s\n",map->C_RGB);
//	printf("%s\n",map->F_RGB);
	printf("S_T%s\n",map->S_T);
}
void parser_for_resolution(t_config *config, char *line)
{

}
void parser_for_texture(char *line, char **part_of_struct, int i)
{
	*part_of_struct = ft_strdup(&line[i]);
}
void parser_for_rgb(char *line, char **part_of_struct)
{

}

void ft_parse_map(t_config *config, char *line)
{
	printf("!%s\n", line);
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
		int b;

		b = 2;
		if (line[i] == 'N')
		{
			parser_for_texture(line, &config->NO_T, b);
		}
		if (line[i] == 'E')
		{
			parser_for_texture(line, &config->EA_T, b);
		}
		if (line[i] == 'W')
		{
			parser_for_texture(line, &config->WE_T, b);
		}
		if (line[i] == 'S' && line[i + 1] == 'O')
		{
			parser_for_texture(line, &config->SO_T, b);
		}
		else if (line[i] == 'S')
		{
			b = 1;
			parser_for_texture(line, &config->S_T, b);
		}
	}
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (line[i] == 'F')
		{
			parser_for_rgb(line, &config->F_RGB);
		}
		else
		{
			parser_for_rgb(line, &config->C_RGB);
		}
	}
	ft_print_st(config);
}