#include "cub.h"
#include <unistd.h>
//#include <mlx.h>

void parse(t_config *map, char *file_name)
{
	char *line;
	int ret;
	int fd;

	(void )map;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("FILE ERROR");
		exit(1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	if (ret == -1)
	{
		printf("GNL ERROR");
		exit(1);
	}
	printf("%s\n", line);
	free(line);
}

void cub(char *file_name)
{
	t_config   map;

	ft_bzero(&map, sizeof(t_config));
	parse(&map, file_name);
}

int main(int ac, char **av)
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
	return 0;
}