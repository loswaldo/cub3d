#include "cub.h"

void	check_line_for_rgb(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		error_output_n_exit("WRONG COLOR");
}

void	parser_for_rgb(char *line, t_rgb *part_of_struct)
{
	int		i;

	i = 1;
	check_line_for_rgb(line);
	while (line[i])
	{
		if (ft_isdigit(line[i]) && part_of_struct->r < 0)
		{
			part_of_struct->r = ft_atoi(&line[i]);
			if (part_of_struct->r > 255 || part_of_struct->r < 0)
				error_output_n_exit("WRONG COLOR");
			while (ft_isdigit(line[i]))
				i++;
			i++;
		}
		if (ft_isdigit(line[i]) && part_of_struct->g < 0)
		{
			part_of_struct->g = ft_atoi(&line[i]);
			if (part_of_struct->g > 255 || part_of_struct->g < 0)
				error_output_n_exit("WRONG COLOR");
			while (ft_isdigit(line[i]))
				i++;
			i++;
		}
		if (ft_isdigit(line[i]) && part_of_struct->b < 0)
		{
			part_of_struct->b = ft_atoi(&line[i]);
			if (part_of_struct->b > 255 || part_of_struct->b < 0)
				error_output_n_exit("WRONG COLOR");
		}
		else
			i++;
	}
}
