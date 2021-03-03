#include "cub.h"

void	ft_init_struct(t_config *config)
{
	config->floor->r = -1;
	config->floor->g = -1;
	config->floor->b = -1;
	config->celling->r = -1;
	config->celling->g = -1;
	config->celling->b = -1;
}

int		check_data_filled(t_config *config)
{
	return (config->floor->r != -1 && config->floor->g != -1
	&& config->floor->b != -1 && config->celling->r != -1
	&& config->celling->g != -1 && config->celling->b != -1
	&& config->NO_T != NULL && config->WE_T != NULL && config->EA_T != NULL
	&& config->SO_T != NULL && config->S_T != NULL && config->Ry != 0
	&& config->Rx != 0);
}

void	parse(t_config *config, char *file_name)
{
	char	*line;
	int		ret;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("FILE ERROR");
		exit(1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (check_line(line, config) && check_data_filled(config))
		{
			ft_parse_map(config, line);
		}
		free(line);
	}
	if (ret == -1)
	{
		printf("GNL ERROR");
		exit(1);
	}
	ft_parse_map(config, line);
	free(line);
}

void	cub(char *file_name)
{
	t_config	config;

	ft_bzero(&config, sizeof(t_config));
	config.floor = malloc(sizeof(t_rgb));
	config.celling = malloc(sizeof(t_rgb));
//	config.NO_texture = malloc(sizeof(t_for_win));
	ft_init_struct(&config);
	parse(&config, file_name);
	rgb_conversion(config.floor, &config.fl);
	rgb_conversion(config.celling, &config.cel);
	map_validation(&config);
	for_window(&config);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		cub(av[1]);
		printf("Yey!");
	}
	else
	{
		printf("Nope!");
	}
	return (0);
}
