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
	double complex c;
	double complex z;
	double complex tmp;
	int		i;
	int		x;
	int		y;
	struct timespec tms;

	clock_gettime(CLOCK_REALTIME,&tms);
	a->time = tms.tv_sec;
	a->micro = tms.tv_nsec;
	x = -1;
	while (++x < IMGF_X && (y = -1) == -1)
		while (++y < IMGF_Y)
			{
				z = 0;
				i = 0;
				c = x / a->mdlb->zoom + a->mdlb->x1 +\
					(y / a->mdlb->zoom + a->mdlb->y1) * I;
				//creal(z) * creal(z) - creal(i) * creal(i)
				while (cabs(z) < 2 && i < a->mdlb->i_max)
				{
					z = z * z + c;
					i++;
				}
				ppx((i == a->mdlb->i_max ? 0x0 : \
							ft_rainbow(i * 1530 / a->mdlb->i_max)), \
							x, y, a->mlx);
			}
	clock_gettime(CLOCK_REALTIME,&tms);
	printf("time to render : %ld . %ld\n", tms.tv_sec - a->time, tms.tv_nsec - a->micro);
}
