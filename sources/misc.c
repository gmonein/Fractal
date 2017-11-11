/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:56:54 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/11 20:13:18 by gmonein          ###   ########.fr       */
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
