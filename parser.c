/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:30:40 by loswaldo          #+#    #+#             */
/*   Updated: 2021/01/21 18:30:43 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//char *ft_free_and_strdup(char const *s1)
//{
//
//}

/*void ft_check_for_map(t_config map, char *line)
{
	int i;

	i = 0;
	if (map.F_RGB != NULL && map.C_RGB != NULL && map.NO_T != NULL && map.WE_T != NULL && map.EA_T != NULL
	&& map.SO_T != NULL && map.Ry != 0 && map.Rx != 0)
	{
		*map.MAP = ft_strdup(&line[i]);
	}
}

int ft_skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
	}
	return (i);
}

int ft_parse_map(char *line, t_config map)
{
	int i;
	i = 0;

	if (line[i] == ' ' || line[i] == '\t')
		i = ft_skip_spaces(line, i);
	if (line[i] == 'R')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (ft_isdigit(line[i]))
		{
			map.Rx = ft_atoi(&line[i]);
		}
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (ft_isdigit(line[i]))
		{
			map.Ry = ft_atoi(&line[i]);
		}
	}
	if (line[i] == 'N')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (!(line[i] == ' ' || line[i] == '\t'))
		{
			map.NO_T = ft_strdup(&line[i]);
		}
	}

	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (!(line[i] == ' ' || line[i] == '\t'))
		{
			map.SO_T = ft_strdup(&line[i]);
		}
	}

	if (line[i] == 'W')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (!(line[i] == ' ' || line[i] == '\t'))
		{
			map.WE_T = ft_strdup(&line[i]);
		}
	}
	if (line[i] == 'E')
	{
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (!(line[i] == ' ' || line[i] == '\t'))
		{
			map.EA_T = ft_strdup(&line[i]);
		}
	}
	else if (line[i] == 'S')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			i = ft_skip_spaces(line, i);
		if (!(line[i] == ' ' || line[i] == '\t'))
		{
			map. S_T = ft_strdup(&line[i]);
		}
	}
	if (line[i] == 'F')
	{
		 map.F_RGB = ft_strdup(&line[i]);
	}
	if (line[i] == 'C')
	{
		map.C_RGB = ft_strdup(&line[i]);
	}
	ft_check_for_map(map, line);
	return 0; *//* todo: alert *//*
}
int ft_parse(t_config map)
{
	char *line;
	int i;
	int fd;

	fd = open ("map.cub", O_RDONLY);
	while ((i = get_next_line (fd, &line)))
	{
		ft_parse_map(line, map);
	}
	return 0;
}
void ft_print_st(t_config map)
{
	int l;

	l = 0;
	printf("%d",map.Rx);
	printf("%d",map.Ry);
	printf("%s",map.SO_T);
	printf("%s",map.EA_T);
	printf("%s",map.WE_T);
	printf("%s",map.NO_T);
	printf("%s",map.C_RGB);
	printf("%s",map.F_RGB);
	printf("%s",map.S_T);
	while (*map.MAP)
	{
		printf("%s",*map.MAP);
		l++;
	}
}*/
/*int main()
{
	t_config map;
	ft_parse(map);
	ft_print_st(map);
}*/


