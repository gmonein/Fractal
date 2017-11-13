/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 01:49:48 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/13 17:17:08 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void		reset_frac(t_fractal *f, int zoom)
{
	if (f->id == ID_MDLB)
		*f = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.5f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 0, 0, 0, 0};
	if (f->id == ID_PDLB)
		*f = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f, 0, 0, 0};
	if (f->id == ID_JUL || f->id == ID_PJUL)
		*f = (t_fractal){ f->id, -2.1, 0.0, -1.2, 1.2, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f, 0, 0, 0};
	if (f->id == ID_NWTN)
		*f = (t_fractal){ ID_NWTN, -2.1f, 1.0f, -1.8f, 1.0f, zoom, 20,
		(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0};
	if (f->id == ID_RSCE)
		*f = (t_fractal){ ID_RSCE, -2.7, 1.0f, -2.1f, 1.0f, zoom * 0.8
		, 20, (2.1f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0};
	if (f->id == ID_TRTL || f->id == ID_ISLD)
		*f = (t_fractal){ f->id, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 0, 0, 0, 0};
	f->zoom_i = 10;
}

int				keyboard_hook(int keycode, t_all *a)
{
	a->keycode = keycode;
	if (keycode == K_Q)
		a->act->i_max += 2;
	else if (keycode == K_W)
		a->act->i_max -= 2;
	else if (keycode == K_A)
		a->pal = (a->pal == 3 ? 0 : a->pal + 1);
	else if (keycode == K_Z)
		a->act->pow++;
	else if (keycode == K_X)
		a->act->pow--;
	else if (keycode == K_E)
		reset_frac(a->act, IMGF_X / 4.2);
	else if (keycode == K_D)
		a->mrdw = (a->mrdw == 1 ? 0 : 1);
	else if (keycode == K_C)
		a->block = (a->block == 1 ? 0 : 1);
	else if (keycode == K_S)
		a->act->smooth = (a->act->smooth >= 1 ? 0 : 1);
	else if (keycode == K_ESC)
		exit_fractal(a);
	else
		return (0);
	redraw(a);
	return (1);
}
