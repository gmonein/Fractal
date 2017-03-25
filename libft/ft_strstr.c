/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:13:03 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 05:55:08 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s, const char *find)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (*find == '\0')
		return ((char *)s);
	while (s[j])
	{
		i = 0;
		while (i < ft_strlen((char *)find) - 1 && s[j]
				&& (unsigned char)find[i] == (unsigned char)s[j])
		{
			i++;
			j++;
		}
		if ((unsigned char)s[j] - (unsigned char)find[i] == 0)
			return ((char *)(s + (j - i)));
		j = (j - i) + 1;
	}
	return (NULL);
}
