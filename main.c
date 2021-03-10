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
void error_output_n_exit(char *str)
{
	int len;

	write(1, "Error\n", 6);
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
			error_output_n_exit("FILE EXTENSION ERROR");
	}
}

void	cub(char *file_name, int is_screenshot)
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

	config.sp = ft_calloc(sizeof(t_sprites), (config.sp_quantity));
	// int i = 0;
	// while (i < config.sp_quantity)
	// {
	// ft_bzero(&config.sp[i], (sizeof(t_sprites)));
	// 	i++;
	// }
	config.wall_dist = malloc(sizeof(double) * config.Rx);
	
	sprites_coord(&config, config.sp);
	output(&config, is_screenshot);
}

void validate_save_argument(const char* arg_save)
{
	const char* save = "--save";

	if (ft_strncmp(arg_save, save, ft_strlen(save) + 1) != 0)
	{
		error_output_n_exit("WRONG ARGUMENT");
	}
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ac == 2)
		{
			check_file_name(av[1]);
			cub(av[1], 0);
			printf("Yey!");
		}
		else if (ac == 3)
		{
			check_file_name(av[1]);
			validate_save_argument(av[2]);
			cub(av[1], 1);
		}
	}
	else
	{
		printf("Nope!");
	}
	return (0);
}
