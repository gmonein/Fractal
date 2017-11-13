/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:01:23 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/12 00:46:25 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_mlx		*make_mlx(void)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, WINDOWS_NAME);
	mlx->image = mlx_new_image(mlx->mlx, WIN_X, WIN_Y);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bpp, &mlx->line_size,
																&mlx->edian);
	mlx->img = make_addr(mlx);
	return (mlx);
}

void		print_usage(void)
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
	ft_putstr_fd(N_NWTN, 2);
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
	a->kfrac = &a->cl.kernels[KRN_MDLB_ID];
	(ft_strcmp(argv, N_JUL) == 0 ? a->kfrac = &a->cl.kernels[KRN_JULIA_ID] : 0);
	(ft_strcmp(argv, N_TRTL) == 0 ? a->kfrac = &a->cl.kernels[KRN_TURTLE_ID] : 0);
	(ft_strcmp(argv, N_ISLD) == 0 ? a->kfrac = &a->cl.kernels[KRN_ISLAND_ID] : 0);
	(ft_strcmp(argv, N_MDLB) == 0 ? a->kfrac = &a->cl.kernels[KRN_MDLB_ID] : 0);
	(ft_strcmp(argv, N_NWTN) == 0 ? a->kfrac = &a->cl.kernels[KRN_NEWTON_ID] : 0);
/*	(ft_strcmp(argv, N_MDLB) == 0 ? a->frac = (void *)mandelbrot : 0);
	(ft_strcmp(argv, N_MDLB) == 0 ? a->frac = (void *)mandelbrot : 0);
	(ft_strcmp(argv, N_PDLB) == 0 ? a->frac = (void *)powdelbrot : 0);
	(ft_strcmp(argv, N_JUL) == 0 ? a->frac = (void *)julia : 0);
	(ft_strcmp(argv, N_PJUL) == 0 ? a->frac = (void *)pow_julia : 0);
	(ft_strcmp(argv, N_NWTN) == 0 ? a->frac = (void *)newton : 0);
	(ft_strcmp(argv, N_RSCE) == 0 ? a->frac = (void *)rosace : 0);
	(ft_strcmp(argv, N_TRTL) == 0 ? a->frac = (void *)turtle : 0);
	(ft_strcmp(argv, N_ISLD) == 0 ? a->frac = (void *)jul_new : 0);
*/	if (a->act == NULL)
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
	init(&a);
	redraw(&a);
//	print_mini_frac(&a);
	return (mlx_loop(a.mlx->mlx));
}
