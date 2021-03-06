/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:13:44 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/15 05:01:17 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int			get_color(t_all *a, t_fr *t)
{
	t->i += 1.0f -
	log((
		log(
			creal(t->z) * creal(t->z) + cimag(t->z) * cimag(t->z)) * 0.50f)
		* DIVLOG) * DIVLOG;
	if (t->i < 0.0f)
		t->i = 0.0f;
	t->i *= 0.10f;
	if ((int)t->i < 0 || (int)t->i > 5)
		t->i = ((double)((int)((double)t->i * 1000000) % 5000000) / 1000000);
	return (ft_gt_colors(a->colors[a->pal][(int)t->i],
	a->colors[a->pal][(int)((int)t->i == 5 ? 0 : t->i + 1)],
	(double)(t->i - (int)t->i)));
}

int			ft_pal(double i, double i_max, int *pal, int p_max)
{
	return (pal[(int)(i * p_max / i_max)]);
}
