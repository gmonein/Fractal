/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 22:19:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/21 20:49:07 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *dst, const char *src)
{
	int		i;
	int		end_dst;

	i = 0;
	while (dst[i])
		i++;
	end_dst = i;
	while (src[i - end_dst])
	{
		dst[i] = src[i - end_dst];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
