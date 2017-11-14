/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 01:50:53 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/14 06:20:39 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void		find_fractal(int x, int y, t_all *a)
{
	y = (double)y / (double)WIN_Y * 4;
	a->act = (y == 0 ? &a->jul : a->act);
	a->act = (y == 1 ? &a->trtl : a->act);
	a->act = (y == 2 ? &a->jlnw : a->act);
	a->act = (y == 3 ? &a->mdlb : a->act);
	a->kfrac = (y == 0 ? (void *)&a->cl.kernels[KRN_JULIA_ID] : (void *)a->kfrac);
	a->kfrac = (y == 1 ? (void *)&a->cl.kernels[KRN_TURTLE_ID] : (void *)a->kfrac);
	a->kfrac = (y == 2 ? (void *)&a->cl.kernels[KRN_ISLAND_ID] : (void *)a->kfrac);
	a->kfrac = (y == 3 ? (void *)&a->cl.kernels[KRN_MDLB_ID] : (void *)a->kfrac);
}

static void		zoom_in(int x, int y, long double i, t_all *a)
{
	size_t		size_x = WIN_X - LEFT_MENU;
	size_t		size_y = WIN_Y;

	double diff_x = (size_x / a->act->zoom) - (size_x / (a->act->zoom + i));
	double diff_y = (size_y / a->act->zoom) - (size_y / (a->act->zoom + i));

	a->act->x1 += diff_x / 2;
	a->act->y1 += diff_y / 2;
	a->act->x1 += diff_x * ((double)x / (double)size_x - 0.5);
	a->act->y1 += diff_y * ((double)y / (double)size_y - 0.5);
	a->act->zoom += i;
}

static void		zoom_out(int x, int y, long double i, t_all *a)
{
	size_t		size_x = WIN_X - LEFT_MENU;
	size_t		size_y = WIN_Y;

	double diff_x = (size_x / a->act->zoom) - (size_x / (a->act->zoom - i));
	double diff_y = (size_y / a->act->zoom) - (size_y / (a->act->zoom - i));

	a->act->x1 += diff_x / 2;
	a->act->y1 += diff_y / 2;
	a->act->x1 += diff_x * ((double)x / (double)size_x - 0.5);
	a->act->y1 += diff_y * ((double)y / (double)size_y - 0.5);
	a->act->zoom -= i;
}

int				mouse_clic(int button, int x, int y, t_all *a)
{
	if (x > 0 && x < WIN_X - LEFT_MENU && y > 0 && y < WIN_Y
		&& (button == 1 || button == 4))
		zoom_in(x, y, a->act->zoom_i *= 1.10f, a);
	else if (x > 0 && x < WIN_X - LEFT_MENU && y > 0 && y < WIN_Y
		&& (button == 2 || button == 5))
		zoom_out(x, y, a->act->zoom_i *= 0.98f, a);
	else if (x > WIN_X - LEFT_MENU)
		find_fractal(x, y, a);
	else
		return (0);
	a->done = 0;
//	redraw(a);
	return (1);
}

int				mouse_pos(int x, int y, t_all *a)
{
	if (x > 0 && y > 0 && x < WIN_X && y < WIN_Y && a->done == 1
	&& a->block == 0)
	{
		a->act->ci = (double)((double)y - IMGF_Y / 2) / 380;
		a->act->c = (double)((double)x - IMGF_X / 2) / 760;
		a->act->pow = (double)((double)x / (double)(WIN_X - LEFT_MENU) * 5);
	a->done = 0;
//		redraw(a);
	}
	return (0);
}
