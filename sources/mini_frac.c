/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_frac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:26:04 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/31 18:22:37 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractal.h>

static void		mini_frac_3(t_all *a, double zoom, t_square b, double pow)
{
	a->frac = (void *)rosace;
	a->other = (t_fractal){ ID_RSCE , -2.7, 1.0f, -0.85f, 1.0f, zoom * 0.8, 20, \
					(2.1f) * zoom, (2.0f) * zoom, 0, 0, 0,\
					0.000001f, 0.001f};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, \
			M_IMGF_X * 2, IMGF_Y + 100);
	a->frac = (void *)newton;
	a->other = (t_fractal){ ID_NWTN ,-1.9f, 1.1f, 1.9f, 0.8f, zoom, 20, \
					(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0,\
					0.000001f, 0.001f};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, \
			M_IMGF_X * 2, IMGF_Y);
}

static void		mini_frac_2(t_all *a, double zoom, t_square b, double pow)
{
	a->frac = (void *)powdelbrot;
	a->other = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50, \
					(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, pow};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, \
			0, IMGF_Y + 100);
	a->frac = (void *)mandelbrot;
	a->other = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -0.85f, 1.2f, zoom, 50, \
					(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom};
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, IMGF_Y);
	mini_frac_3(a, zoom, b, pow);
}

static void		mini_frac_1(t_all *a, double zoom, t_square b, double pow)
{
	double		c;
	double		ci;

	pow = (pow == 1 || pow == 0 ? 3 : pow);
	c = (a->act->c == 0 ? -0.5f : a->act->c);
	ci = (a->act->ci == 0 ? 0.7f : a->act->ci);
	a->act = &a->other;
	a->mlx = &a->mini_mlx;
	a->frac = (void *)julia;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -0.85f, 1.2f, zoom, 50, \
					(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0};
	a->other.c = c;
	a->other.ci = ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, \
			a->mlx->image, IMGF_X / 4, IMGF_Y);
	a->frac = (void *)pow_julia;
	a->other = (t_fractal){ ID_PJUL,-2.1, 0.0, -0.85f, 1.2, zoom, 50, \
					(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, pow};
	a->other.c = c;
	a->other.ci = ci;
	fractal(a, b);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, \
			M_IMGF_X, IMGF_Y + 100);
	mini_frac_2(a, zoom, b, pow);
}

void		print_mini_frac(t_all *a)
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
