/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 19:00:35 by gmonein           #+#    #+#             */
/*   Updated: 2017/02/09 17:04:18 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memalloc(size_t size)
{
	void	*s;

	if ((s = malloc(size)) == NULL)
		return (NULL);
	ft_bzero(s, size);
	return (s);
}
