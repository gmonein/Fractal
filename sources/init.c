/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:57:11 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/31 14:31:12 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_mlx		*make_mlx(void)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, WINDOWS_NAME);
	mlx->image = mlx_new_image(mlx->mlx, IMGF_X, IMGF_Y);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bpp, &mlx->line_size,
																&mlx->edian);
	mlx->img = make_addr(mlx);
	return (mlx);
}

static int			**make_m_addr(t_mlx *mlx)
{
	int		**img;
	int		i;
	int		steps;

	i = 0;
	steps = M_IMGF_Y;
	img = (int **)malloc(sizeof(int *) * (M_IMGF_Y + 1));
	img[0] = (int *)mlx->addr;
	while (++i < steps)
		img[i] = (int *)&mlx->addr[i * M_IMGF_X * 4];
	img[i] = NULL;
	return (img);
}

t_mlx		make_mini_mlx(t_all *a)
{
	t_mlx		mlx;

	mlx.mlx = a->mlx->mlx;
	mlx.win = a->mlx->win;
	mlx.image = mlx_new_image(mlx.mlx, M_IMGF_X, M_IMGF_Y);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bpp, &mlx.line_size,
																&mlx.edian);
	mlx.img = make_m_addr(&mlx);
	return (mlx);
}
