/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 22:45:29 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/11 22:52:21 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	c2;

	tmp = (unsigned char *)ptr;
	c2 = (unsigned char)c;
	while (n)
	{
		if (*tmp == c2)
			return (tmp);
		tmp++;
		n--;
	}
	return (NULL);
}
