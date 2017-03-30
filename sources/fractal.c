/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/30 16:28:20 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		fractal(t_all *a, t_square b)
{
	int		by;
	t_fr	var;

	b.x1--;
	by = b.y1;
	if (a->act->id == ID_JUL || a->act->id == ID_PJUL)
		var.c = a->act->c + a->act->ci * I;
	while (++b.x1 < b.x2 && (b.y1 = by - 1) != -2)
		while (++b.y1 < b.y2)
			a->frac(a, b, &var);
}

void		mandelbrot(t_all *a, t_square b, t_fr *v)
{
	v->z = 0;
	v->i = 0;
	v->c = b.x1 / a->mdlb.zoom + a->mdlb.x1 +\
		(b.y1 / a->mdlb.zoom + a->mdlb.y1) * I;
	v->smoothcolor = (a->smooth == 1 ? exp(-fabs(creal(v->z))) : a->mdlb.i_max);
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 4 \
												&& v->i < a->mdlb.i_max)
	{
		v->z = v->z * v->z + v->c;
		v->i++;
		v->smoothcolor += (a->smooth == 1 ? exp(-cabs(v->z)) : 0);
	}
	ppx(v->i == a->mdlb.i_max ? 0x0\
		: ft_rainbow((int)((v->i * (v->smoothcolor / a->mdlb.i_max) \
					+ a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}

void		julia(t_all *a, t_square b, t_fr *v)
{
	v->smoothcolor = (a->smooth == 1 ? exp(-fabs(creal(v->z))) : a->jul.i_max);
	v->i = 0;
	v->z = b.x1 / a->jul.zoom + a->jul.x1 +\
		(b.y1 / a->jul.zoom + a->jul.y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 4\
											&& v->i < a->jul.i_max)
	{
		v->z = v->z * v->z + v->c;
		v->i++;
		v->smoothcolor += (a->smooth == 1 ? exp(-cabs(v->z)) : 0);
	}
	ppx(v->i == a->jul.i_max ? 0x0\
			: ft_rainbow((int)((v->i * (v->smoothcolor / a->jul.i_max) \
						+ a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}

void		powdelbrot(t_all *a, t_square b, t_fr *v)
{
	v->z = 0;
	v->i = 0;
	v->c = b.x1 / a->pdlb.zoom + a->pdlb.x1 +\
		(b.y1 / a->pdlb.zoom + a->pdlb.y1) * I;
	v->smoothcolor = (a->smooth == 1 ? exp(-fabs(creal(v->z))) : a->pdlb.i_max);
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 4 \
												&& v->i < a->pdlb.i_max)
	{
		v->z = cpow(v->z, a->pdlb.pow) + v->c;
		v->i++;
		v->smoothcolor += (a->smooth == 1 ? exp(-cabs(v->z)) : 0);
	}
	ppx(v->i == a->pdlb.i_max ? 0x0\
		: ft_rainbow((int)((v->i * (v->smoothcolor / a->pdlb.i_max) \
					+ a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}

void		pow_julia(t_all *a, t_square b, t_fr *v)
{
	v->smoothcolor = (a->smooth == 1 ? exp(-fabs(creal(v->z))) : a->pjul.i_max);
	v->i = 0;
	v->z = b.x1 / a->pjul.zoom + a->pjul.x1 +\
		(b.y1 / a->pjul.zoom + a->pjul.y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 4\
											&& v->i < a->pjul.i_max)
	{
		v->z = cpow(v->z, a->pjul.pow) + v->c;
		v->i++;
		v->smoothcolor += (a->smooth == 1 ? exp(-cabs(v->z)) : 0);
	}
	ppx(v->i == a->pjul.i_max ? 0x0\
			: ft_rainbow((int)((v->i * (v->smoothcolor / a->pjul.i_max) \
						+ a->i_inc) * 30) % 1530), b.x1, b.y1, a->mlx);
}
