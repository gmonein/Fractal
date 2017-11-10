# include "libft.h"

char	*ft_strduptochar(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = ft_strsub(str, 0, i);
	return (res);
}
