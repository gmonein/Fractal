/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:13:44 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/01 23:14:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int			get_color(t_all *a,t_fr *t, int i_max)
{
	t->i += 1.0f -
	log((log(creal(t->z) * creal(t->z) + cimag(t->z) * cimag(t->z)) * 0.50f)
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
