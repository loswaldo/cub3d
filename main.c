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
void error_output(char *str)
{
	int len;

	len = ft_strlen(str);
	write(1, str, len);
	exit(1);
}

void check_file_name(char *file_name)
{
	int len;
	int i;
	char *str;

	str = "buc.";
	len = ft_strlen(file_name);
	i = 0;
	while (i <= 3)
	{
		if (file_name[(len - i) - 1] == str[i])
			i++;
		else
			error_output("FILE EXTENSION ERROR");
	}
}

void	cub(char *file_name)
{
	t_config	config;

	ft_bzero(&config, sizeof(t_config));
	config.floor = malloc(sizeof(t_rgb));
	config.celling = malloc(sizeof(t_rgb));
	config.win = malloc(sizeof (t_for_win));
	ft_init_struct(&config);
	parse(&config, file_name);
	rgb_conversion(config.floor, &config.fl);
	rgb_conversion(config.celling, &config.cel);
	map_validation(&config);

	config.sp = calloc(sizeof(t_sprites), config.sp_quantity + 1);
	config.wall_dist = malloc(sizeof(double) * config.Rx);

	sprites_coord(&config, config.sp);
	output(&config);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		check_file_name(av[1]);
		cub(av[1]);
		printf("Yey!");
	}
	else
	{
		printf("Nope!");
	}
	return (0);
}
