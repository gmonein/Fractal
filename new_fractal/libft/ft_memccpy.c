/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 22:31:10 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 04:15:54 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dst;
	unsigned char	*src;
	unsigned char	x;

	dst = (unsigned char *)s1;
	src = (unsigned char *)s2;
	x = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if ((*dst++ = *src++) == x)
			return (dst);
		i++;
	}
	return (NULL);
}
