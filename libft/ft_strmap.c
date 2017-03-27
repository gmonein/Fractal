/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 06:47:22 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 07:12:28 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	int		len;

	len = 0;
	if (s == NULL)
		return (NULL);
	while (s[len])
		len++;
	fresh = (char *)malloc(sizeof(char) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	fresh[len] = '\0';
	while (len--)
		fresh[len] = (*f)(s[len]);
	return (fresh);
}
