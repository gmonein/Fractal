/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 19:06:33 by bsouchet          #+#    #+#             */
/*   Updated: 2017/11/11 20:45:04 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_gt_colors(int clr1, int clr2, double val)
{
	int		r;
	int		g;
	int		b;

	if (val > 1.0)
		val = 1.0;
	else if (val < 0.0)
		val = 0.0;
	r = floor((double)((clr1 >> 16) & 0xFF) -
	(((double)((clr1 >> 16) & 0xFF) - (double)((clr2 >> 16) & 0xFF)) * val));
	g = floor((double)((clr1 >> 8) & 0xFF) -
	(((double)((clr1 >> 8) & 0xFF) - (double)((clr2 >> 8) & 0xFF)) * val));
	b = floor((double)((clr1) & 0xFF) - (((double)((clr1) & 0xFF) \
		- (double)((clr2) & 0xFF)) * val));
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
