
#include "cub.h"

void error_output_n_exit(const char *str)
{
	int len;

	write(1, "Error\n", 6);
	len = ft_strlen(str);
	write(1, str, len);
	exit(1);
}
