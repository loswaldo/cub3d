#include "cub.h"

int		ft_is_identifier(char *line, int i, t_config *config)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parser_for_texture(line, &config->NO_T, 2);
	else if (line[i] == 'S' && (line[i + 1] == 'O' || line[i + 1] == ' '))
		parser_for_texture(line, line[i + 1] == 'O'
		? &config->SO_T : &config->S_T, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		parser_for_texture(line, &config->WE_T, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		parser_for_texture(line, &config->EA_T, 2);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		parser_for_resolution(config, line);
	else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		parser_for_rgb(line, line[i] == 'F' ? config->floor : config->celling);
	else if (line[i] == '1' && check_data_filled(config))
		return (1);
	else
	{
		printf("WRONG STRING OR NOT ENOUGH SHTUKI");
		exit(1);
	}
	return (0);
}

void	rgb_conversion(t_rgb *color, int *part_of_struct)
{
	if (color->r)
		*part_of_struct += color->r << 16;
	if (color->g)
		*part_of_struct += color->g << 8;
	if (color->b)
		*part_of_struct += color->b;
}

int		check_line(char *line, t_config *config)
{
	int		i;

	i = 0;
	if (line[i] == '\0')
	{
		if (check_data_filled(config) && config->PRE_MAP)
		{
			printf("MAP IS NOT MAP!");
			exit(1);
		}
		return (0);
	}
	i = ft_skip_spaces(line, i);
	if (line[i] == '\0')
		return (0);
	return (ft_is_identifier(line, i, config));
}

char	*ft_fill_spaces(char *str, int len)
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

int		map_symbol_check(char c, const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	part_of_map_checker(t_config *config, int x, int y)
{
	int		i;
	int		j;

	j = 0;
	x += -1;
	y += -1;
	if ((x < 0 || x >= config->map_width) || (y < 0 || y >= config->map_height))
	{
		printf("MAP IS NOT VALID!!!!!!!");
		printf("x = %d y = %d", x, y);
		exit(1);
	}
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			if (!(map_symbol_check(config->MAP[y + j][x + i], "102NWES")))
			{
				printf("MAP IS NOT VALID!!!!!!!");
				printf("x = %d y = %d", x, y);
				exit(1);
			}
			else
				printf("all good \n");
			i++;
		}
		j++;
		if (y < 0 || y > config->map_height)
		{
			printf("MAP IS NOT VALID!!!!!!!");
			printf("x = %d y = %d", x, y);
			exit(1);
		}
	}
}

void	map_checker(t_config *config)
{
	int		x;
	int		y;
	int		check;

	check = 0;
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (config->MAP[y][x] == 'S' || config->MAP[y][x] == 'N'
			|| config->MAP[y][x] == 'W' || config->MAP[y][x] == 'E')
			{
				check++;
				config->pl_pos_y = x;
				config->pl_pos_x = y;
			}
			x++;
		}
		y++;
	}
	if (check != 1)
	{
		printf("MAP ERROR(number of start position)");
		exit(1);
	}
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (map_symbol_check(config->MAP[y][x], "02NWES"))
			{
				part_of_map_checker(config, x, y);
			}
			x++;
		}
		y++;
	}
	y = 0;
	while (config->MAP[y])
	{
		printf("%s\n", config->MAP[y]);
		y++;
	}
}

void	map_validation(t_config *config)
{
	char	*tmp;
	char	**str;
	int		y;

	y = 0;
	tmp = ft_strdup(config->PRE_MAP);
	free(config->PRE_MAP);
	config->PRE_MAP = ft_strtrim(tmp, "\n");
	free(tmp);
	str = ft_split(config->PRE_MAP, '\n');
	while (str[y])
	{
		if (str[y] != 0 && config->map_width > (int)ft_strlen(str[y]))
			str[y] = ft_fill_spaces(str[y], config->map_width);
		y++;
	}
	config->map_height = y - 1;
	free(config->PRE_MAP);
	config->MAP = malloc((config->map_height + 1) * sizeof(char*));
	y = 0;
	while (y <= config->map_height)
	{
		config->MAP[y] = malloc(config->map_width * sizeof(char));
		y++;
	}
	y = 0;
	while (str[y])
	{
		config->MAP[y] = ft_strdup(str[y]);
		y++;
	}
	config->MAP[y] = NULL;
	y = 0;
	while (str[y])
	{
		free(str[y]);
		y++;
	}
	free(str);
	map_checker(config);
}
