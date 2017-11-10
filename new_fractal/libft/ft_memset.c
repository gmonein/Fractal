/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 21:40:04 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/13 01:56:58 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*fresh;

	fresh = (unsigned char *)ptr;
	while (num)
	{
		*fresh = (unsigned char)value;
		num--;
		if (num)
			fresh++;
	}
	return (ptr);
}
