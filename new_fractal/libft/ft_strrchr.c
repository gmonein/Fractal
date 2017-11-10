/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:04:03 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 05:22:09 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	while (*str)
		str++;
	if ((char)c == '\0')
		return ((char *)str);
	str--;
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str--;
	}
	return (0);
}
