/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:52:47 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/30 18:37:18 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	zoom(int x, int y, int i, t_all *a)
{
	double	dx;
	double	dy;

	dx = x;
	dy = y;
	dx *= (a->act->zoom + i) / (a->act->zoom);
	dy *= (a->act->zoom + i) / (a->act->zoom);
	a->act->x1 += (((double)dx - (double)IMGF_MX) / (a->act->zoom));
	a->act->x2 += (((double)dx - (double)IMGF_MX) / (a->act->zoom));
	a->act->y1 += (((double)dy - (double)IMGF_MY) / (a->act->zoom));
	a->act->y2 += (((double)dy - (double)IMGF_MY) / (a->act->zoom));
	a->act->zoom += i;
}

int		keyboard_hook(int keycode, t_all *a)
{
	if (keycode == K_X)
		a->act->pow += 0.1;
	else if (keycode == K_Z)
		a->act->pow -= 0.1;
	else if (keycode == K_C)
	{
		a->i_inc += 10;
		if (a->i_inc > 1530)
			a->i_inc = 0;
	}
	else if (keycode == K_I)
		a->act->i_max++;
	else if (keycode == K_O)
		a->act->i_max--;
	else if (keycode == K_S)
		return (0);
	redraw(a);
	return (0);
}

int		mouse_pos(int x, int y, t_all *a)
{
	int		i;
	if (x > 0 && y > 0 && x < IMGF_X && y < IMGF_Y && a->done == 1)
	{
		if (a->act->id == ID_JUL || a->act->id == ID_PJUL)
		{
			a->act->ci = (double)((double)y - IMGF_Y / 2) / 380;
			a->act->c = (double)((double)x - IMGF_X / 2) / 760;
		}
		else if (a->act->id == ID_PDLB)
		{
			a->act->pow = (double)((double)(x + y - 50) / 10 + 20) / 10;
		}
		else
			return (0);
		redraw(a);
	}
	return (0);
}
int		mouse_clic(int button, int x, int y, t_all *a)
{
	a->zoom_i += (a->zoom_i / 2);
	a->mouse.x = x;
	a->mouse.y = y;
	zoom(x, y, a->zoom_i, a);
	redraw(a);
	return (0);
}

int		loop_hook(t_all *a)
{
	return (0);
}

int			main(int argc, char **argv)
{
	t_all		a;

	int			zoom;
	void		(*frac)(struct s_all *, t_square);
	a.pow_i = 1;
	a.frame = 0;
	a.thread_cnt = atoi(argv[1]);
	a.thread = malloc_thread(a.thread_cnt);
	zoom = IMGF_X / 4.2;
	a.zoom_i = 10;
	a.mdlb = (t_fractal){ ID_MDLB, -2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom};
	a.pdlb = (t_fractal){ ID_PDLB, -2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom, 0, 0, 1.0f};
	a.jul = (t_fractal){ ID_JUL,-2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom, 0, 0};
	a.pjul = (t_fractal){ ID_PJUL,-2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom, 0, 0, 3.0f};
	a.quit = 0;
	a.mlx = make_mlx();
//	a.frac = (void *)mandelbrot;
//	a.act = &a.mdlb;
//	a.frac = (void *)julia;
//	a.act = &a.jul;
	a.frac = (void *)powdelbrot;
	a.act = &a.pdlb;
//	a.frac = (void *)pow_julia;
//	a.act = &a.pjul;
	mlx_hook(a.mlx->win, 2, (1L << 0), keyboard_hook, &a);
	mlx_hook(a.mlx->win, 6, (1L << 6), mouse_pos, &a);
	mlx_loop_hook(a.mlx->mlx, loop_hook, &a);
	mlx_mouse_hook(a.mlx->win, mouse_clic, &a);
	redraw(&a);
	return (mlx_loop(a.mlx->mlx));
}
