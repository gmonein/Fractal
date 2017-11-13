/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/12 00:53:12 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		fractal(t_all *a, t_square b)
{
	int		by;
	t_fr	var;

	b.x1--;
	by = b.y1;
	if (a->act->id == ID_JUL || a->act->id == ID_PJUL
	|| a->act->id == ID_TRTL || a->act->id == ID_ISLD)
		var.c = a->act->c + a->act->ci * I;
	while (++b.x1 < b.x2 && (b.y1 = by - 1) != -2)
		while (++b.y1 < b.y2)
			a->frac(a, b, &var);
}

void		pow_julia(t_all *a, t_square b, t_fr *v)
{
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 16
	&& v->i < a->act->i_max)
	{
		v->z = cpow(v->z, a->pjul.pow) + v->c;
		v->i++;
	}
	if (a->smooth == 0)
		ppx(v->i == a->act->i_max ? 0x0 : get_color(a, v)
		, b.x1, b.y1, a->mlx);
	else
		ppx(v->i == a->act->i_max ? 0x0 :
		ft_pal(v->i, a->act->i_max, a->colors[a->pal], a->p_max)
		, b.x1, b.y1, a->mlx);
}

t_complex	fn(t_complex z)
{
	return (z * z * z - 1.0f);
}

void		newton(t_all *a, t_square b, t_fr *v)
{
	v->h = a->act->der + a->act->der * I;
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +\
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (v->i < a->act->i_max)
	{
		v->dz = (fn(v->z + v->h) - fn(v->z)) / v->h;
		v->z0 = v->z - fn(v->z) / v->dz;
		v->i++;
		if (cabs(v->z0 - v->z) < a->act->lim)
			break ;
		v->z = v->z0;
	}
	ppx(v->i == a->act->i_max ? 0x0 :
	ft_pal(v->i, a->act->i_max, a->colors[a->pal], a->p_max)
	, b.x1, b.y1, a->mlx);
}

void		rosace(t_all *a, t_square b, t_fr *v)
{
	v->h = a->act->der + a->act->der * I;
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +
			(b.y1 / a->act->zoom + a->act->y1) * I;
	while (v->i < a->act->i_max
	&& creal(v->z) * creal(v->z) + cimag(v->z) + cimag(v->z) < 16)
	{
		v->dz = (fn(v->z + v->h) - fn(v->z)) / v->h;
		v->z0 = v->z - fn(v->z) / v->dz;
		v->i++;
		if (cabs(v->z0 - v->z) < a->act->lim)
			break ;
		v->z = v->z0 * v->z0;
	}
	ppx(v->i == a->act->i_max ? 0x0 :
	ft_pal(v->i, a->act->i_max, a->colors[a->pal], a->p_max)
	, b.x1, b.y1, a->mlx);
}
