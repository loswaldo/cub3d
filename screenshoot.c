#include "cub.h"

static void		filling_file_screenshot(int fd, t_config *config)
{
	int	i;
	int	j;
	int	color;

	i = config->Ry;
	while (--i >= 0)
	{
		j = -1;
		while (++j < config->Rx)
		{
			color = *(int*)(config->win->addr + (i * config->win->line_len
												 + j * (config->win->bpp / 8)));
			write(fd, &color, 4);
		}
	}
}

void			continue_screenshot(t_config *config, int fd)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = config->Rx
				  * config->Ry * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &config->Rx, 4);
	write(fd, &config->Ry, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void			screenshot(t_config *config)
{
	int fd;
	int size_screen;
	int zero;
	int size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	size_screen = config->Rx
				  * config->Ry * 4 + 54;
	zero = 0;
	size = config->Rx
		   * config->Ry;
	if (fd < 0)
		write(1, "Error\n", 6);
	continue_screenshot(config, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	filling_file_screenshot(fd, config);
	close(fd);
}

