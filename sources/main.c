/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:52:47 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 01:16:16 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	zoom_in(int x, int y, int i, t_all *a)
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

void	zoom_out(int x, int y, int i, t_all *a)
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
	a->act->zoom -= i;
}

void	reset_frac(t_fractal *f, int zoom)
{
	if (f->id == ID_MDLB)
		*f = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.5f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom};
	if (f->id == ID_PDLB)
		*f = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f};
	if (f->id == ID_JUL || f->id == ID_PJUL)
		*f = (t_fractal){ f->id , -2.1, 0.0, -1.2, 1.2, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f};
	if (f->id == ID_NWTN)
		*f = (t_fractal){ ID_NWTN ,-2.1f, 1.0f, -1.8f, 1.0f, zoom, 20,
		(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f};
	if (f->id == ID_RSCE)
		*f = (t_fractal){ ID_RSCE , -2.7, 1.0f, -2.1f, 1.0f, zoom * 0.8
		, 20, (2.1f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f};
	if (f->id == ID_TRTL || f->id == ID_ISLD)
		*f = (t_fractal){ f->id , -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0};
	f->zoom_i = 10;
}

int		keyboard_hook(int keycode, t_all *a)
{
	a->keycode = keycode;
	if (keycode == K_Q)
		a->act->i_max++;
	else if (keycode == K_W)
		a->act->i_max--;
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
		a->smooth = (a->smooth == 1 ? 0 : 1);
	else
		return (0);
	redraw(a);
	return (1);
}

int		mouse_pos(int x, int y, t_all *a)
{
	int		i;
	if (x > 0 && y > 0 && x < IMGF_X && y < IMGF_Y && a->done == 1
	&& a->block == 0)
	{
		if (a->act->id == ID_JUL || a->act->id == ID_PJUL
		|| a->act->id == ID_TRTL || a->act->id == ID_ISLD)
		{
			a->act->ci = (double)((double)y - IMGF_Y / 2) / 380;
			a->act->c = (double)((double)x - IMGF_X / 2) / 760;
		}
		else if (a->act->id == ID_PDLB)
			a->act->pow = (double)((double)(x + y - 50) / 10 + 20) / 10;
		else
			return (0);
		redraw(a);
	}
	return (0);
}

void	find_fractal(int x, int y, t_all *a)
{
	a->act = (x == 0 && y == 0 ? &a->mdlb : a->act);
	a->act = (x == 0 && y == 1 ? &a->pdlb : a->act);
	a->act = (x == 1 && y == 0 ? &a->nwtn : a->act);
	a->act = (x == 1 && y == 1 ? &a->rsce : a->act);
	a->act = (x == 2 && y == 0 ? &a->jul : a->act);
	a->act = (x == 2 && y == 1 ? &a->pjul : a->act);
	a->act = (x == 3 && y == 0 ? &a->trtl : a->act);
	a->act = (x == 3 && y == 1 ? &a->jlnw : a->act);
	a->frac = (x == 0 && y == 0 ? (void *)mandelbrot : (void *)a->frac);
	a->frac = (x == 0 && y == 1 ? (void *)powdelbrot : (void *)a->frac);
	a->frac = (x == 1 && y == 0 ? (void *)newton : (void *)a->frac);
	a->frac = (x == 1 && y == 1 ? (void *)rosace : (void *)a->frac);
	a->frac = (x == 2 && y == 0 ? (void *)julia : (void *)a->frac);
	a->frac = (x == 2 && y == 1 ? (void *)pow_julia : (void *)a->frac);
	a->frac = (x == 3 && y == 0 ? (void *)turtle : (void *)a->frac);
	a->frac = (x == 3 && y == 1 ? (void *)jul_new : (void *)a->frac);
}

int		mouse_clic(int button, int x, int y, t_all *a)
{
	if (x > 0 && x < IMGF_X && y > 0 && y < IMGF_Y && button == 1)
		zoom_in(x, y, a->act->zoom_i *= 1.10f, a);
	else if (x > 0 && x < IMGF_X && y > 0 && y < IMGF_Y && button == 2)
		zoom_out(x, y, a->act->zoom_i *= (1 / 1.10f), a);
	else if (x > 0 && x < IMGF_X && y > IMGF_Y && y < WIN_Y)
		find_fractal(x / M_IMGF_X, (y - IMGF_Y) / M_IMGF_Y, a);
	else
		return (0);
	redraw(a);
	return (1);
}

void			init_fractal(t_all *a, int zoom)
{
	a->mdlb = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.5f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom};
	a->mdlb.zoom_i = 10;
	a->pdlb = (t_fractal){ ID_PDLB, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f};
	a->pdlb.zoom_i = 10;
	a->jul = (t_fractal){ ID_JUL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0};
	a->jul.zoom_i = 10;
	a->pjul = (t_fractal){ ID_PJUL,-2.1, 0.0, -1.2, 1.2, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 3.0f};
	a->pjul.zoom_i = 10;
	a->nwtn = (t_fractal){ ID_NWTN ,-2.1f, 1.0f, -1.8f, 1.0f, zoom, 20,
		(2.0f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f};
	a->nwtn.zoom_i = 10;
	a->rsce = (t_fractal){ ID_RSCE , -2.7, 1.0f, -2.1f, 1.0f, zoom * 0.8, 20,
		(2.1f) * zoom, (2.0f) * zoom, 0, 0, 0, 0.000001f, 0.001f};
	a->rsce.zoom_i = 10;
	a->trtl = (t_fractal){ ID_TRTL, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0};
	a->trtl.zoom_i = 10;
	a->jlnw = (t_fractal){ ID_ISLD, -2.1f, 0.0f, -1.2f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0};
	a->jlnw.zoom_i = 10;
}

static void	init_colors(t_all *a)
{
	a->colors[0][0] = 0x7F1637;
	a->colors[0][1] = 0x047878;
	a->colors[0][2] = 0xFFB733;
	a->colors[0][3] = 0xF57336;
	a->colors[0][4] = 0xC22121;
	a->colors[0][5] = 0x7F1637;
	a->colors[1][0] = 0xFF0000;
	a->colors[1][1] = 0xFFFF00;
	a->colors[1][2] = 0x00FF00;
	a->colors[1][3] = 0x00FFFF;
	a->colors[1][4] = 0x0000FF;
	a->colors[1][5] = 0xFF00FF;
	a->colors[2][0] = 0x2E4600;
	a->colors[2][1] = 0x486B00;
	a->colors[2][2] = 0xA2C523;
	a->colors[2][3] = 0x7D4427;
	a->colors[2][4] = 0xA2C523;
	a->colors[2][5] = 0x486B00;
	a->colors[3][0] = 0xD4D4D4;
	a->colors[3][1] = 0x8C8C8C;
	a->colors[3][2] = 0x666666;
	a->colors[3][3] = 0x3D3D3D;
	a->colors[3][4] = 0x666666;
	a->colors[3][5] = 0x8C8C8C;
}

void		print_usage()
{
	ft_putstr_fd("usage : fractol [fractals]\n", 2);
	ft_putstr_fd(" fractals :\n --> ", 2);
	ft_putstr_fd(N_MDLB, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_PDLB, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_JUL, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_PJUL, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd( N_NWTN, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_RSCE, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_TRTL, 2);
	ft_putstr_fd("\n --> ", 2);
	ft_putstr_fd(N_ISLD, 2);
	ft_putstr_fd("\n", 2);
}

int			parsing(char *argv, t_all *a)
{
	a->act = NULL;
	a->frac = NULL;
	(ft_strcmp(argv, N_MDLB) == 0 ? a->act = &a->mdlb : 0);
	(ft_strcmp(argv, N_PDLB) == 0 ? a->act = &a->pdlb : 0);
	(ft_strcmp(argv, N_JUL) == 0 ? a->act = &a->jul : 0);
	(ft_strcmp(argv, N_PJUL) == 0 ? a->act = &a->pjul : 0);
	(ft_strcmp(argv, N_NWTN) == 0 ? a->act = &a->nwtn : 0);
	(ft_strcmp(argv, N_RSCE) == 0 ? a->act = &a->rsce : 0);
	(ft_strcmp(argv, N_TRTL) == 0 ? a->act = &a->trtl : 0);
	(ft_strcmp(argv, N_ISLD) == 0 ? a->act = &a->jlnw : 0);
	(ft_strcmp(argv, N_MDLB) == 0 ? a->frac = (void *)mandelbrot : 0);
	(ft_strcmp(argv, N_PDLB) == 0 ? a->frac = (void *)powdelbrot : 0);
	(ft_strcmp(argv, N_JUL) == 0 ? a->frac = (void *)julia : 0);
	(ft_strcmp(argv, N_PJUL) == 0 ? a->frac = (void *)pow_julia : 0);
	(ft_strcmp(argv, N_NWTN) == 0 ? a->frac = (void *)newton : 0);
	(ft_strcmp(argv, N_RSCE) == 0 ? a->frac = (void *)rosace : 0);
	(ft_strcmp(argv, N_TRTL) == 0 ? a->frac = (void *)turtle : 0);
	(ft_strcmp(argv, N_ISLD) == 0 ? a->frac = (void *)jul_new : 0);
	if (a->act == NULL)
	{
		print_usage();
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_all		a;

	if (argc == 2)
		if (parsing(argv[1], &a) == 0)
			return (0);
	if (argc != 2)
	{
		print_usage();
		return (0);
	}
	init_colors(&a);
	a.pal = 2;
	a.pow_i = 1;
	a.smooth = 0;
	a.thread_cnt = 16;
	a.thread = malloc_thread(a.thread_cnt);
	a.p_max = 6;
	a.mlx = make_mlx();
	a.mini_mlx = make_mini_mlx(&a);
	init_fractal(&a, IMGF_X / 4.2);
	mlx_hook(a.mlx->win, 2, (1L << 0), keyboard_hook, &a);
	mlx_hook(a.mlx->win, 6, (1L << 6), mouse_pos, &a);
	mlx_mouse_hook(a.mlx->win, mouse_clic, &a);
	redraw(&a);
	print_mini_frac(&a);
	return (mlx_loop(a.mlx->mlx));
}
