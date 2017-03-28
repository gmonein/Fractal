/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:54 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 22:33:38 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_cpx		cpx_mul(t_cpx a, t_cpx b)
{
	t_cpx	res;

	res.r = a.r * b.r - a.i * b.i;
	res.i = a.r * b.i + a.i * b.r;
	return (res);
}

t_cpx		cpx_add(t_cpx a, t_cpx b)
{
	t_cpx	res;

	res.r = a.r + b.r;
	res.i = a.i + b.i;
	return (res);
}

int		ft_rainbow(int i)
{
	int		r;
	int		g;
	int		b;

	r = 255 * (double)sin(i * 2 * PI / 1530);
	g = 255 * (double)sin((i + 255) * 2 * PI / 1530);
	b = 255 * (double)sin((i + 510) * 2 * PI / 1530);
	r = (r >= 0 ? r : 0);
	g = (g >= 0 ? g : 0);
	b = (b >= 0 ? b : 0);
/*
	r = (i >= 0 ? 0xFF : 0);
	r = (i >= 255 ? 510 - i : r);
	r = (i >= 510 ? 0 : r);
	r = (i >= 1020 ? i - 1020 : r);
	r = (i >= 1275 ? 255 : r);
	g = (i >= 0 ? i : 0);
	g = (i >= 255 ? 255 : g);
	g = (i >= 765 ? 1020 - i : g);
	g = (i >= 1020 ? 0 : g);
	b = (i >= 510 ? i - 510 : 0);
	b = (i >= 765 ? 255 : b);
	b = (i >= 1275 ? 1530 - i : b);
	*/
	return ((r << 16) + (g << 8) + b);
}

int			**make_addr(t_mlx *mlx)
{
	int		**img;
	int		i;
	int		steps;

	i = 0;
	steps = IMGF_Y;
	img = (int **)malloc(sizeof(int *) * (IMGF_Y + 1));
	img[0] = (int *)mlx->addr;
	while (++i < steps)
		img[i] = (int *)&mlx->addr[i * IMGF_X * 4];
	img[i] = NULL;
	return (img);
}

int			ppx(int color, int x, int y, t_mlx *mlx)
{
	if (x < 0 || y < 0 || x > IMGF_X || y > IMGF_Y)
		return (-1);
	mlx->img[y][x] = color;
	return (1);
}
