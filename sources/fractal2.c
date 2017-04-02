/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:23:56 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 02:25:15 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		mandelbrot(t_all *a, t_square b, t_fr *v)
{
	v->z = 0;
	v->i = 0;
	v->c = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 1 << 8
	&& v->i < a->act->i_max)
	{
		v->z = v->z * v->z + v->c;
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

void		julia(t_all *a, t_square b, t_fr *v)
{
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 16
	&& v->i < a->act->i_max)
	{
		v->z = v->z * v->z + v->c;
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

void		turtle(t_all *a, t_square b, t_fr *v)
{
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (cimag(v->z) * cimag(v->z) < 10
	&& v->i < a->act->i_max)
	{
		v->z = v->z * v->z * v->z * v->z * v->z + v->c;
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

void		jul_new(t_all *a, t_square b, t_fr *v)
{
	v->i = 0;
	v->z = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (cimag(v->z) * cimag(v->z) + creal(v->z) * creal(v->z) < 4
	&& v->i < a->act->i_max)
	{
		v->z = (v->z * v->z - v->z) * (v->z * v->z - v->z)
			+ (v->z + v->c) * (v->z + v->c) * (v->z + v->c);
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

void		powdelbrot(t_all *a, t_square b, t_fr *v)
{
	v->z = 0;
	v->i = 0;
	v->c = b.x1 / a->act->zoom + a->act->x1 +
		(b.y1 / a->act->zoom + a->act->y1) * I;
	while (creal(v->z) * creal(v->z) + cimag(v->z) * cimag(v->z) < 16
	&& v->i < a->act->i_max)
	{
		v->z = cpow(v->z, a->pdlb.pow) + v->c;
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
