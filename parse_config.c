#include "cub.h"

int		ft_skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	parser_for_resolution(t_config *config, char *line)
{
	int i;

	i = 1;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
		config->Rx = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
		config->Ry = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i = ft_skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		printf("WRONG NUMBER FOR RESOLUTION");
		exit(1);
	}
}

void	parser_for_texture(char *line, char **part_of_struct, int i)
{
	if (!(*part_of_struct))
		*part_of_struct = ft_strdup(&line[i + 1]);
	else
	{
		printf("REITERATION TEXTURE");
		exit(1);
	}
}

void	ft_parse_map(t_config *config, char *line)
{
	char *tmp;

	if (config->map_width < (int)ft_strlen(line))
		config->map_width = ft_strlen(line);
	if (!(config->PRE_MAP))
		config->PRE_MAP = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(config->PRE_MAP, "\n");
		free(config->PRE_MAP);
		config->PRE_MAP = ft_strjoin(tmp, line);
		free(tmp);
	}
}
