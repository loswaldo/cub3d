#include "cub.h"

void parser_for_rgb_f(char *line, t_config *config, t_rgb *part_of_struct)
{
	int i;

	i = 1;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && part_of_struct->r < 0)
		{
			part_of_struct->r = ft_atoi(&line[i]);
			if (part_of_struct->r > 255 && part_of_struct->r < 0)
			{
				printf("WRONG COLOR");
				exit(1);
			}
			while (ft_isdigit(line[i]))
			{
				i++;
			}
			i++;
		}
		if (ft_isdigit(line[i]) && part_of_struct->g < 0)
		{
			part_of_struct->g = ft_atoi(&line[i]);
			if (part_of_struct->g > 255 && part_of_struct->g < 0)
			{
				printf("WRONG COLOR");
				exit(1);
			}
			while (ft_isdigit(line[i]))
			{
				i++;
			}
			i++;
		}
		if (ft_isdigit(line[i]) && part_of_struct->b < 0)
		{
			part_of_struct->b = ft_atoi(&line[i]);
			if (part_of_struct->b > 255 && part_of_struct->b < 0)
			{
				printf("WRONG COLOR");
				exit(1);
			}
		}
		else
		{
			i++;
		}
	}
}

