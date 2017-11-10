/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:26:07 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 06:03:58 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s, const char *find, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (*find == '\0')
		return ((char *)s);
	if (n > ft_strlen(s))
		n = ft_strlen(s);
	while (j < n)
	{
		while (find[i] != s[j] && j < n)
			j++;
		while (find[i] == s[j] && j < n)
		{
			j++;
			i++;
		}
		if (!find[i])
			return ((char *)(s + (j - i)));
		j = j - i + 1;
		i = 0;
	}
	return (NULL);
}
