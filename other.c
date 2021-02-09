#include "cub.h"

int ft_is_identifier(char *line, int i, t_config *config)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
	{
		return (1);
	}
	if (line[i] == 'S' && (line[i + 1] == 'O' || line[i + 1] == ' '))
	{
		return (1);
	}
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
	{
		return (1);
	}
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
	{
		return (1);
	}
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		return (1);
	}
	if (line[i] == 'F' && line[i + 1] == ' ')
	{
		return (1);
	}
	if (line[i] == 'C' && line[i + 1] == ' ')
	{
		return (1);
	}
	if (line[i] == '1' && check_data_filled(config))
	{
		return (1);
	}
	printf("WRONG STRING");
	exit (1);
}
void rgb_conversion(t_rgb *color, int *part_of_struct)
{
	if (color->r)
	{
		*part_of_struct += color->r << 16;
	}
	if (color->g)
	{
		*part_of_struct += color->g << 8;
	}
	if (color->b)
	{
		*part_of_struct += color->b;
	}
}
int check_line(char *line, t_config *config)
{
	int i;

	i = 0;
	if (line[i] == '\0')
	{
		return (0);
	}
	i = ft_skip_spaces(line, i);
	if (line[i] == '\0')
	{
		return (0); //уточнить валидная ли строка просто с проблелами
	}
	return (ft_is_identifier(line,i, config));
}
char *ft_fill_spaces(char *str, int len)
{
	char	*b;
	int		i;

	i = 0;
	b = malloc(sizeof(char) * (len + 1));
	if (!b)
		return (0);
	while (str[i] != 0)
	{
		b[i] = str[i];
		i++;
	}
	while (i < len)
	{
		b[i] = ' ';
		i++;
	}
	b[i] = '\0';
	free(str);
	return (b);
}
void map_validation(t_config *config)
{
	char *tmp;
	char **str;
	int y;

	y = 0;
	tmp = ft_strdup(config->MAP);
	free(config->MAP);
	config->MAP = ft_strtrim(tmp, "\n");
	free(tmp);

	str = ft_split(config->MAP, '\n');
	while (str[y++])
	{
		if (str[y] != 0 && config->map_width > (int)ft_strlen(str[y]))
		{
			str[y] = ft_fill_spaces(str[y], config->map_width);
		}
	}
	config->map_height = y - 1;
	free (config->MAP);
	config->MAP = NULL;
	y = 0;
	while (str[y])
	{
		ft_parse_map(config, str[y]);
		y++;
	}
	printf("%s", config->MAP);
//	printf("height = %d", config->map_height);
}
