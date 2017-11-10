/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:58:12 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/18 07:58:43 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_alloc(unsigned int n, int base, int *len)
{
	int		i;
	char	*s;

	i = 0;
	while (n > 0)
	{
		n = n / base;
		i++;
	}
	if (!(s = (char *)malloc(sizeof(char) * i + 2)))
		return (NULL);
	s[i + 1] = '\0';
	(*len) = i;
	return (s);
}

char			*ft_uitoa_base(unsigned int num, int base)
{
	char		*str;
	int			len;

	if (base > 16 || base < 2)
		return (NULL);
	len = 0;
	str = ft_alloc(num, base, &len);
	if (num == 0)
		str[0] = '0';
	while (len--)
	{
		str[len] = (num % base) + (num % base > 9 ? 'A' - 10 : '0');
		num /= base;
	}
	return (str);
}
