#include "cub.h"

void	check_line_for_rgb(char *line)
{
	int				i;
	int				count;
	const char *	error = "WRONG COLOR";

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else if (line[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		error_output_n_exit(error);
}

int skip_digits(const char *line)
{
	int i = 0;

	while (line[i] && ft_isdigit(line[i])) {
		++i;
	}
	return i;
}

int is_valid_color(int color)
{
	return (color <= 255 && color >= 0);
}

int parser_for_color(int * color_in_struct, const char * line)
{
	const char * color_error = "WRONG COLOR";

	*color_in_struct = ft_atoi(line);
	if (!is_valid_color(*color_in_struct))
		error_output_n_exit(color_error);
	return skip_digits(line);
}

void	parser_for_rgb(char *line, t_rgb *part_of_struct)
{
	int		i;

	i = 1;
	check_line_for_rgb(line);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			if (part_of_struct->r < 0)
			{
				i += parser_for_color(&part_of_struct->r, line + i);
			}
			else if (part_of_struct->g < 0)
			{
				i += parser_for_color(&part_of_struct->g, line + i);
			}
			else if (part_of_struct->b < 0)
			{
				i += parser_for_color(&part_of_struct->b, line + i);
				continue ;
			}
		}
		i++;
	}
}
