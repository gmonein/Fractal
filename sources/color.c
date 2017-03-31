/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:13:44 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/01 01:51:00 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int			linear_color(double i, int max, t_palette *p)
{
	double		index;
	double		adjust;
	int			c;

	index = fmod(i, 5) / 5;
	adjust = fmod(index, 1.0f / 5) * 5;
	return (ft_gt_colors(a->colors[a->pal][(int)t->i],
	a->colors[a->pal][(int)(t->i + 1)],
	(double)(t->i - (int)t->i)));
}

int			get_newton_color(t_all *a,t_fr *t, int i_max)
{
	if (t->i >= i_max)
		return (0x000000);
	t->i += 1.0f -
	log((log(cabs(t->z)) / 2.0f) / log(2)) / log(2);
	if (t->i < 0.0f)
		t->i = 0.0f;
	t->i /= 10.0f;
	if ((int)t->i < 0 || (int)t->i > 5)
		return (0);

	return (ft_gt_colors(a->colors[a->pal][(int)t->i],
	a->colors[a->pal][(int)(t->i + 1)],
	(double)(t->i - (int)t->i)));
}

int			get_color(t_all *a,t_fr *t, int i_max)
{
	t->i += 1.0f -
	log((log(creal(t->z) * creal(t->z) + cimag(t->z) * cimag(t->z)) / 2.0f)
															/ log(2)) / log(2);
	if (t->i < 0.0f)
		t->i = fabs(0.0f);
	t->i /= 10.0f;
	if ((int)t->i < 0 || (int)t->i > 5)
		return (0);
	t->i = fmod(t->i, 2);
	return (ft_gt_colors(a->colors[a->pal][(int)t->i],
	a->colors[a->pal][(int)(t->i + 1)],
	(double)(t->i - (int)t->i)));
}
