#include "get_next_line.h"

size_t	ft_strlenn(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoinn(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2) + 1))))
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[l])
	{
		str[i] = s2[l];
		i++;
		l++;
	}
	str[i] = 0;
	free(s1);
	return (str);

}

char	*ft_strchar(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdupp(char *s1)
{
	char	*b;
	int		i;

	i = 0;
	b = malloc(sizeof(char) * (ft_strlenn(s1) + 1));
	if (!b)
		return (0);
	while (s1[i] != 0)
	{
		b[i] = s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
