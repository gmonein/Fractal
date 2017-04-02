/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:53:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 03:04:17 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	free_thread(t_o_thread **thread, int count)
{
	while (count > 0)
	{
		free(thread[count - 1]);
		count--;
	}
	free(thread);
}

void	exit_fractal(t_all *a)
{
	mlx_destroy_window(a->mlx->mlx, a->mlx->win);
	mlx_destroy_image(a->mlx->mlx, a->mlx->image);
	mlx_destroy_image(a->mlx->mlx, a->mini_mlx.image);
	free(a->mlx->img);
	free(a->mlx);
	free_thread(a->thread, a->thread_cnt);
	exit(0);
}
