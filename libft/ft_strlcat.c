/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:36:55 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 03:17:08 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char *src, size_t n)
{
	size_t		i;
	size_t		end_dst;

	i = 0;
	while (dst[i] && i < n)
		i++;
	end_dst = i;
	while (src[i - end_dst] && i < n - 1)
	{
		dst[i] = src[i - end_dst];
		i++;
	}
	if (end_dst < n)
		dst[i] = '\0';
	return (end_dst + ft_strlen(src));
}
