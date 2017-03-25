/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 22:31:10 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 03:25:58 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	if (n == 0 || s1 == s2)
		return (s1);
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n)
	{
		*c1 = *c2;
		n--;
		c1++;
		c2++;
	}
	return (s1);
}
