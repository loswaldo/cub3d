#include "cub.h"

void parser_for_rgb_f(char *line, t_config *config)
{
	int i;

	i = 1;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && config->floor->r == 0)
		{
			config->floor->r = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
			{
				i++;
			}
			i++;
		}
		if (ft_isdigit(line[i]) && config->floor->g == 0)
		{
			config->floor->g = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
			{
				i++;
			}
			i++;
		}
		if (ft_isdigit(line[i]) && config->floor->b)
		{
			config->floor->b = ft_atoi(&line[i]);
		}
		else
		{
			i++;
		}
	}
	ft_print_st(config);
	printf("parser rgb: %s\n", line);
}

