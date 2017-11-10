/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:29:06 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/16 01:49:13 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dst, char *src, size_t n)
{
	size_t		i;
	size_t		end_dst;

	i = 0;
	while (dst[i])
		i++;
	end_dst = i;
	while (src[i - end_dst] && (i - end_dst) < n)
	{
		dst[i] = src[i - end_dst];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
