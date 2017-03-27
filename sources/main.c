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

void	zoom(int x, int y, int i, t_all *a)
{
	double	dx;
	double	dy;

	dx = x;
	dy = y;
	dx *= (a->mdlb->zoom + i) / (a->mdlb->zoom);
	dy *= (a->mdlb->zoom + i) / (a->mdlb->zoom);
	a->mdlb->x1 += (((double)dx - (double)IMGF_MX) / (a->mdlb->zoom));
	a->mdlb->x2 += (((double)dx - (double)IMGF_MX) / (a->mdlb->zoom));
	a->mdlb->y1 += (((double)dy - (double)IMGF_MY) / (a->mdlb->zoom));
	a->mdlb->y2 += (((double)dy - (double)IMGF_MY) / (a->mdlb->zoom));
	a->mdlb->zoom += i;
//	printf("x1 %lf y1 %lf\n",a->mdlb->x1, a->mdlb->y1);
}

int		keyboard_hook(int keycode, t_all *a)
{
	if (keycode == 'z')
	{
		a->zoom_i += (a->zoom_i / 2);
		zoom(a->mouse.x, a->mouse.y, a->zoom_i, a);
	}
	else if (keycode == 'x')
	{
		a->zoom_i += (a->zoom_i / 2);
		zoom(1024, 1024, a->zoom_i, a);
	}
	else if (keycode == 'i')
		a->mdlb->i_max++;
	else if (keycode == 'o')
		a->mdlb->i_max--;
	mandelbrot(a);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
	return (0);
}

int		mouse_pos(int x, int y, t_all *a)
{
	return (0);
}
int		mouse_clic(int button, int x, int y, t_all *a)
{
	a->zoom_i += (a->zoom_i / 2);
	a->mouse.x = x;
	a->mouse.y = y;
	zoom(x, y, a->zoom_i, a);
	mandelbrot(a);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
	return (0);
}

int		loop_hook(t_all *a)
{
	struct timespec tms;

	clock_gettime(CLOCK_REALTIME,&tms);
	a->frame++;
	if (tms.tv_sec != a->time)
	{
		a->time = tms.tv_sec;
	//	printf("%u\n", (unsigned)tms.tv_sec);
	}
	return (0);
}
int			main(int argc, char **argv)
{
	t_all		a;
	t_fractal	mdlb;
	int			zoom;
	a.frame = 0;
	zoom = 300;
	a.zoom_i = 10;
	mdlb = (t_fractal){-2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom};
	a.mdlb = &mdlb;
	a.mlx = make_mlx();
	mandelbrot(&a);
	mlx_put_image_to_window(a.mlx->mlx, a.mlx->win, a.mlx->image, 0, 0);
	mlx_hook(a.mlx->win, 2, (1L << 0), keyboard_hook, &a);
	mlx_hook(a.mlx->win, 6, (1L << 6), mouse_pos, &a);
	mlx_loop_hook(a.mlx->mlx, loop_hook, &a);
	mlx_mouse_hook(a.mlx->win, mouse_clic, &a);
	return (mlx_loop(a.mlx->mlx));
}
