/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:52:47 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/26 22:50:46 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractal.h"


int		keyboard_hook(int keycode, t_all *a)
{
	return (0);
}

int		mouse_pos(int x, int y, t_all *a)
{
	return (0);
}
int		mouse_clic(int button, int x, int y, t_all *a)
{
	a->mdlb->zoom += 10;
	a->mdlb->x1 -= x / a->mdlb->zoom;
	a->mdlb->y1 -= y / a->mdlb->zoom;
	mandelbrot(a);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
	return (0);
}

int			main(int argc, char **argv)
{
	t_all		a;
	t_fractal	mdlb;
	int			zoom;

	zoom = 300;
	mdlb = (t_fractal){-2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom};
	a.mdlb = &mdlb;
	a.mlx = make_mlx();
	mandelbrot(&a);
	mlx_put_image_to_window(a.mlx->mlx, a.mlx->win, a.mlx->image, 0, 0);
	mlx_hook(a.mlx->win, 2, (1L << 0), keyboard_hook, &a);
	mlx_hook(a.mlx->win, 6, (1L << 6), mouse_pos, &a);
	mlx_mouse_hook(a.mlx->win, mouse_clic, &a);
	return (mlx_loop(a.mlx->mlx));
}
