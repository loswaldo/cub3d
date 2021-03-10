#include "cub.h"

void	parse(t_config *config, char *file_name)
{
	char	*line;
	int		ret;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("FILE ERROR");
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
		error_output_n_exit("GNL ERROR");
	}
	ft_parse_map(config, line);
	free(line);
}

void sprites_coord(t_config *config, t_sprites *sprite)
{
	int x;
	int y;
	int i;
	
	x = 0;
	y = 0;
	i = 0;
	while (config->MAP[y])
	{
		while (config->MAP[y][x])
		{
			if (config->MAP[y][x] == '2')
			{
				sprite[i].x = ((double)y + 0.5);
				sprite[i].y = ((double)x + 0.5);
				i++;
			}
			x++;	
		}
		x = 0;
		y++;
	}
}