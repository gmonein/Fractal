/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:57:11 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 16:00:30 by gmonein          ###   ########.fr       */
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
