# include "libft.h"

char	**dup_double_tab(char **d_tab)
{
	int		i;
	char	**res;

	i = 0;
	while (d_tab[i])
		i++;
	if (!(res = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (d_tab[i])
	{
		res[i] = ft_strdup(d_tab[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
