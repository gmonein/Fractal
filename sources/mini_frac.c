/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_frac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:26:04 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/12 00:29:14 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void		mini_frac_4(t_all *a, double zoom, t_square b)
{
	a->frac = (void *)jul_new;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0.193421, 0.781579,
		0, 0, 0, 0};
	a->other.c = a->c;
	a->other.ci = a->ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
			M_IMGF_X + M_IMGF_X + M_IMGF_X, IMGF_Y + 100);
}

static void		mini_frac_3(t_all *a, double zoom, t_square b)
{
	a->frac = (void *)rosace;
	a->other = (t_fractal){ ID_RSCE, -2.7, 1.0f, -0.85f, 1.0f, zoom * 0.8, 20,
		(2.1f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
		M_IMGF_X, IMGF_Y + 100);
	a->frac = (void *)newton;
	a->other = (t_fractal){ ID_NWTN, -3.0f, 1.0f, -1.0f, 1.7f, zoom, 20,
		(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f, 0};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
		M_IMGF_X, IMGF_Y);
	a->frac = (void *)turtle;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -0.9f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0.193421, 0.781579, 0, 0
		, 0, 0};
	a->other.c = a->c;
	a->other.ci = a->ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
		M_IMGF_X + M_IMGF_X + M_IMGF_X, IMGF_Y);
	mini_frac_4(a, zoom, b);
}

static void		mini_frac_2(t_all *a, double zoom, t_square b, double pow)
{
	a->frac = (void *)powdelbrot;
	a->other = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, pow, 0, 0, 0};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
		0, IMGF_Y + 100);
	a->frac = (void *)mandelbrot;
	a->other = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -0.85f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 0, 0, 0, 0};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, IMGF_Y);
	mini_frac_3(a, zoom, b);
}

static void		mini_frac_1(t_all *a, double zoom, t_square b, double pow)
{
	pow = (pow == 1 || pow == 0 ? 3 : pow);
	a->c = (a->act->c == 0 ? -0.5f : a->act->c);
	a->ci = (a->act->ci == 0 ? 0.7f : a->act->ci);
	a->act = &a->other;
	a->mlx = &a->mini_mlx;
	a->frac = (void *)julia;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -0.85f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (2.4f) * zoom, 0.193421, 0.781579, 0, 0, 0, 0};
	a->other.c = a->c;
	a->other.ci = a->ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win,
		a->mlx->image, M_IMGF_X + M_IMGF_X, IMGF_Y);
	a->frac = (void *)pow_julia;
	a->other = (t_fractal){ ID_PJUL, -2.1, 0.0, -0.85f, 1.2, zoom, 50,
		(0.6f + 2.1f) * zoom, (2.4f) * zoom, 0.193421, 0.781579, pow, 0, 0, 0};
	a->other.c = a->c;
	a->other.ci = a->ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image,
		M_IMGF_X + M_IMGF_X, IMGF_Y + 100);
	mini_frac_2(a, zoom, b, pow);
}

void			print_mini_frac(t_all *a)
{
	t_square	b;
	double		zoom;
	void		*b1;
	void		*b2;
	void		*b3;

	zoom = M_IMGF_X / 4.2;
	b = (t_square){0, 0, M_IMGF_X, M_IMGF_Y};
	b1 = a->mlx;
	b2 = a->frac;
	b3 = a->act;
	mini_frac_1(a, zoom, b, a->act->pow);
	a->mlx = b1;
	a->frac = b2;
	a->act = b3;
}
