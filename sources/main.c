/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 21:52:47 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 22:36:26 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		*thread_fonc(void *b)
{
	t_all		*a;
	t_o_thread	*t;

	t = b;
	a = t->all;
	fractal(a, t->zone);
	pthread_exit(NULL);
}

t_o_thread	**malloc_thread(int count)
{
	t_o_thread		**thread;

	thread = (t_o_thread **)malloc(sizeof(t_o_thread *) * (count + 1));
	thread[count] = NULL;
	while (--count != -1)
		thread[count] = (t_o_thread *)malloc(sizeof(t_o_thread));
	return (thread);
}

void	create_thread(t_all *a, t_o_thread **thread, int count)
{
	int			x_inc;
	int			x;
	int			ret;

	x_inc = IMGF_X / count;
	x = 0;
	while (--count != -1)
	{
		thread[count]->id = count;
		thread[count]->all = a;
		thread[count]->zone = (t_square){x, 0, x + x_inc, IMGF_Y};
		ret = pthread_create(&thread[count]->thread, NULL, \
								thread_fonc, thread[count]);
		x += x_inc;
	}
}

void	redraw(t_all *a)
{
	int		i;
	void	*ret;

	i = -1;
	a->done = 0;
	create_thread(a, a->thread, a->thread_cnt);
	while (a->thread[++i])
		pthread_join(a->thread[i]->thread, &ret);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
	a->done = 1;
}

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
	if (keycode == K_E)
		a->pow_i += 0.05;
	else if (keycode == K_Z)
	{
		a->i_inc += 10;
		if (a->i_inc > 1530)
			a->i_inc = 0;
	}
	else if (keycode == K_I)
		a->mdlb->i_max++;
	else if (keycode == K_O)
		a->mdlb->i_max--;
	redraw(a);
	return (0);
}

int		mouse_pos(int x, int y, t_all *a)
{
	int		i;
	if (x > 0 && y > 0 && x < IMGF_X && y < IMGF_Y && a->done == 1)
	{
		a->mdlb->ci = (double)((double)y - IMGF_Y / 2) / 380;
		a->mdlb->c = (double)((double)x - IMGF_X / 2) / 760;
	//	a->mdlb->pow = (double)((double)x / 10 + 20) / 10;
		redraw(a);
	}
	return (0);
}
int		mouse_clic(int button, int x, int y, t_all *a)
{
	a->zoom_i += (a->zoom_i / 2);
	a->mouse.x = x;
	a->mouse.y = y;
	zoom(x, y, a->zoom_i, a);
	redraw(a);
	return (0);
}

int		loop_hook(t_all *a)
{
	return (0);
}

int			main(int argc, char **argv)
{
	t_all		a;
	t_fractal	mdlb;

	int			zoom;
	void		(*frac)(struct s_all *, t_square);
	a.pow_i = 1;
	a.frame = 0;
	a.thread_cnt = atoi(argv[1]);
	a.thread = malloc_thread(a.thread_cnt);
	zoom = IMGF_X / 4.2;
	a.zoom_i = 10;
	mdlb = (t_fractal){-2.1, 0.0, -1.2, 1.2, zoom, 50, \
					(0.6 + 2.1) * zoom, (1.2 + 1.2) * zoom};
	a.quit = 0;
	a.mdlb = &mdlb;
	a.mlx = make_mlx();
	a.frac = (void *)mandelbrot;
	//a.frac = (void *)julia;
	mlx_hook(a.mlx->win, 2, (1L << 0), keyboard_hook, &a);
	mlx_hook(a.mlx->win, 6, (1L << 6), mouse_pos, &a);
	mlx_loop_hook(a.mlx->mlx, loop_hook, &a);
	mlx_mouse_hook(a.mlx->win, mouse_clic, &a);
	return (mlx_loop(a.mlx->mlx));
}
