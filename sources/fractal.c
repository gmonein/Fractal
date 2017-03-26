/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/26 22:50:49 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		mandelbrot(t_all *a)
{
	t_cpx	c;
	t_cpx	z;
	int		i;
	int		x;
	int		y;
	
	x = -1;
	while (++x < IMGF_X && (y = -1) == -1)
		while (++y < IMGF_)
			{
				c.r = x / a->mdlb->zoom + a->mdlb->x1;
				c.i = y / a->mdlb->zoom + a->mdlb->y1;
				z = (t_cpx){0, 0};
				i = -1;
				while (z.r*z.r + z.i*z.i < 4 && ++i < a->mdlb->i_max)
						z = cpx_add(cpx_mul(z, z), c);
				ppx((i == a->mdlb->i_max ? 0x0 : \
							ft_rainbow(i * 1530 / a->mdlb->i_max)), \
							x, y, a->mlx);
			}
}
