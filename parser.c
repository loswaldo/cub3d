#include "cub.h"

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

void sprites_coord(t_config *config, t_sprites *s)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	while(config->MAP[y])
	{
		while(config->MAP[y][x])
		{
			if (config->MAP[y][x] == '2')
			{
				s[i].x = x + 0.5;
				s[i].y = y + 0.5;
			}
			x++;
		}
		y++;
	}
}