/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 01:49:48 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/14 06:46:40 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void		reset_frac(t_fractal *f, int zoom)
{
	if (f->id == ID_JUL)
		*f = (t_fractal){ ID_JUL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 1000,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0.067546, -0.75, 0, 0, 0, 0, 1};
	if (f->id == ID_MDLB)
		*f = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.5f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 0, 0, 0, 0, 1};
	if (f->id == ID_TRTL)
		*f = (t_fractal){ ID_TRTL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 1000,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, -0.071053, 0.632895, 0, 0, 0, 0, 1};
	if (f->id == ID_ISLD)
		*f = (t_fractal){ ID_ISLD, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 250,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, -0.518421, -0.225, 0, 0, 0, 0, 1};
	f->zoom_i = 10;
}

int				keyboard_hook(int keycode, t_all *a)
{
	int		c_boost = 2;
	int		m_boost = 8;
	a->keycode = keycode;
	if (keycode == K_Q)
		a->act->i_max += 1 + a->act->i_max * 0.01;
	else if (keycode == K_W && a->act->i_max > 10)
		a->act->i_max -= 1 + a->act->i_max * 0.01;
	else if (keycode == K_A)
		a->pal = (a->pal == 3 ? 0 : a->pal + 1);
	else if (keycode == K_Z)
		a->act->pow++;
	else if (keycode == K_X)
		a->act->pow--;
	else if (keycode == K_UP)
		a->act->ci -= c_boost / a->act->zoom;
	else if (keycode == K_DOWN)
		a->act->ci += c_boost / a->act->zoom;
	else if (keycode == K_LEFT)
		a->act->c -= c_boost / a->act->zoom;
	else if (keycode == K_RIGHT)
		a->act->c += c_boost / a->act->zoom;
	else if (keycode == K_T)
		a->act->y1 -= m_boost / a->act->zoom;
	else if (keycode == K_G)
		a->act->y1 += m_boost / a->act->zoom;
	else if (keycode == K_F)
		a->act->x1 -= m_boost / a->act->zoom;
	else if (keycode == K_H)
		a->act->x1 += m_boost / a->act->zoom;
	else if (keycode == K_E)
		reset_frac(a->act, (WIN_X - LEFT_MENU) / 4.2);
	else if (keycode == K_D)
		a->mrdw = (a->mrdw == 1 ? 0 : 1);
	else if (keycode == K_C)
		a->block = (a->block == 1 ? 0 : 1);
	else if (keycode == K_S)
		a->act->smooth = (a->act->smooth >= 1 ? 0 : 1);
	else if (keycode == K_R)
		printf("c: %lf ci:%lf\n", a->act->c, a->act->ci);
	else if (keycode == K_ESC)
		exit_fractal(a);
	else
		return (0);
	a->done = 0;
	//redraw(a);
	return (1);
}
