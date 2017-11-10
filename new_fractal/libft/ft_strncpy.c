/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:40:08 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/16 03:11:47 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t		i;
	size_t		j;

	j = n;
	while (j--)
		((unsigned char *)dst)[j] = '\0';
	i = 0;
	while (n-- && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
