#include "cub.h"

int		ft_is_identifier(char *line, int i, t_config *config)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parser_for_texture(line, &config->NO_T, 2);
	else if (line[i] == 'S' && (line[i + 1] == 'O' || line[i + 1] == ' '))
		parser_for_texture(line, line[i + 1] == 'O'
		? &config->SO_T : &config->S_T, line[i + 1] == 'O' ? 2 : 1);
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
		error_output_n_exit("WRONG STRING OR NOT ");
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
			error_output_n_exit("MAP IS NOT MAP!");
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

void print_map(char **map) { /* todo: delete this function */
	puts("Start printing!");

	int y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
	puts("Success printing!");
}

void	part_of_map_checker(t_config *config, int x, int y)
{
	int		i;
	int		j;

	j = 0;
	x += -1;
	y += -1;
	if ((x < 0 || x >= config->map_width) || (y < 0 || y >= config->map_height))
		error_output_n_exit("MAP IS NOT VALID!");
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			if (!(map_symbol_check(config->MAP[y + j][x + i], "102NWES")))
				error_output_n_exit("MAP IS NOT VALID!!!!!!!");
			i++;
		}
		j++;
		if (y < 0 || y > config->map_height)
			error_output_n_exit("MAP IS NOT VALID!!!!!!!");
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
				config->direction = config->MAP[y][x];
				config->MAP[y][x] = '0';
				config->pl_pos_y = (float)(x + 0.01);
				config->pl_pos_x = (float)(y + 0.01);
			}
			x++;
		}
		y++;
	}
	if (check != 1)
		error_output_n_exit("MAP ERROR(number of start position)");
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

}

void sprites_counter(t_config *config)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (config->PRE_MAP[i])
	{
		if (config->PRE_MAP[i] == '2')
		{
			count++;
		}
		i++;
	}
	config->sp_quantity = count;
}

void	map_validation(t_config *config)
{
	char	*tmp;
	int		y;

	y = 0;
	sprites_counter(config);
	tmp = config->PRE_MAP;
	config->PRE_MAP = ft_strtrim(config->PRE_MAP, "\n");
	free(tmp);
	config->MAP = ft_split(config->PRE_MAP, '\n');
	while (config->MAP[y])
	{
		if (config->MAP[y] != 0 && config->map_width > (int)ft_strlen(config->MAP[y]))
			config->MAP[y] = ft_fill_spaces(config->MAP[y], config->map_width);
		y++;
	}
	config->map_height = y - 1;
	free(config->PRE_MAP);
	config->PRE_MAP = NULL;
	map_checker(config);
}
