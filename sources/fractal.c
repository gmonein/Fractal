/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 22:34:53 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		fractal(t_all *a, t_square b)
{
	int		by;
	t_fr	var;

	b.x1--;
	by = b.y1;
	while (++b.x1 < b.x2 && (b.y1 = by - 1) != -2)
		while (++b.y1 < b.y2)
			a->frac(a, b, &var);
}

void		mandelbrot(t_all *a, t_square b, t_fr *v)
{
	v->z = 0;
	v->i = 0;
	v->c = b.x1 / a->mdlb->zoom + a->mdlb->x1 +\
		(b.y1 / a->mdlb->zoom + a->mdlb->y1) * I;
	v->smoothcolor = exp(-cabs(v->z));
	while (creal(v->z) * creal(v->z) + cimag(v->i) * cimag(v->i) < 4 && v->i < a->mdlb->i_max)
	{
		v->z = v->z * v->z + v->c;
		v->i++;
		v->smoothcolor += exp(-cabs(v->z));
	}
	ppx(v->i == a->mdlb->i_max ? 0x0 : ft_rainbow((int)((v->i * (v->smoothcolor / a->mdlb->i_max) + a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}

void		julia(t_all *a, t_square b, t_fr *v)
{
	v->smoothcolor = exp(-fabs(creal(v->z)));
	v->i = 0;
	v->z = b.x1 / a->mdlb->zoom + a->mdlb->x1 +\
		(b.y1 / a->mdlb->zoom + a->mdlb->y1) * I;
	while (creal(v->z) *  creal(v->z) +  cimag(v->z) * cimag(v->z) < 4 && v->i < a->mdlb->i_max)
	{
		v->z = v->z * v->z + v->c;
		v->i++;
		v->smoothcolor += exp(-cabs(v->z));
	}
	ppx(v->i == a->mdlb->i_max ? 0x0 : ft_rainbow((int)((v->i * (v->smoothcolor / a->mdlb->i_max) + a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}
