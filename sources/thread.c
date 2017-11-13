/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:32:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/13 17:28:05 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_o_thread			**malloc_thread(int count)
{
	t_o_thread		**thread;

	thread = (t_o_thread **)malloc(sizeof(t_o_thread *) * (count + 1));
	thread[count] = NULL;
	while (--count != -1)
		thread[count] = (t_o_thread *)malloc(sizeof(t_o_thread));
	return (thread);
}

static void			*thread_fonc(void *b)
{
	t_all		*a;
	t_o_thread	*t;

	t = b;
	a = t->all;
	fractal(a, t->zone);
	pthread_exit(NULL);
}

static void			create_thread(t_all *a, t_o_thread **thread, int count)
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

void				draw_frac(t_all *a, t_clkernel kernel, size_t offset[3], size_t size[3])
{
	memcpy(kernel.global_worksize, size, sizeof(size_t) * 3);
	memcpy(kernel.offset, offset, sizeof(size_t) * 3);
	cl_run(&a->cl, &kernel);
}

void				menu(t_all *a)
{
	double		zoom = LEFT_MENU / 4.2;
	void		*b1;
	int			pos = 0;

	a->cl.mems[MEM_ARG_ID].ptr = &a->other;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -0.85f, 1.2f, zoom, a->act->i_max,
		(0.6f + 2.1f) * zoom, (2.4f) * zoom, a->act->ci, a->act->c, 0, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_JULIA_ID], (size_t[3]){WIN_X - LEFT_MENU, WIN_Y / 6 * pos, 0}, (size_t[3]){LEFT_MENU, WIN_Y / 6, 0});

	pos++;
	a->other = (t_fractal){ ID_JUL, -2.1f, 0.0f, -0.9f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, a->act->ci, a->act->c, 0, 0
		, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_TURTLE_ID], (size_t[3]){WIN_X - LEFT_MENU, WIN_Y / 6 * pos, 0}, (size_t[3]){LEFT_MENU, WIN_Y / 6, 0});

	pos++;
	a->other = (t_fractal){ ID_JUL, -1.5f, 0.0f, -1.0f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, a->act->ci, a->act->c,
		0, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_ISLAND_ID], (size_t[3]){WIN_X - LEFT_MENU, WIN_Y / 6 * pos, 0}, (size_t[3]){LEFT_MENU, WIN_Y / 6, 0});

	pos++;
	a->other = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -0.85f, 1.2f, zoom, 50,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 0, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_MDLB_ID], (size_t[3]){WIN_X - LEFT_MENU, WIN_Y / 6 * pos, 0}, (size_t[3]){LEFT_MENU, WIN_Y / 6, 0});
	clFinish(a->cl.command_queue);
}

void				redraw(t_all *a)
{
	int		i;
	void	*ret;

	i = -1;
	a->done = 0;

//	create_thread(a, a->thread, a->thread_cnt);
//	while (a->thread[++i])
//		pthread_join(a->thread[i]->thread, &ret);
	a->cl.mems[MEM_ARG_ID].ptr = a->act;
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 0);
	a->cl.mems[MEM_OARG_ID].ptr = &a->colors[a->pal];
	refrash_clmem(&a->cl, &a->cl.mems[MEM_OARG_ID], CL_MEM_WRITE, 0);
	cl_run(&a->cl, a->kfrac);
//	clFinish(a->cl.command_queue);
//	if (clEnqueueReadBuffer(a->cl.command_queue, a->cl.mems[MEM_PIXEL_ID].mem,
//		CL_TRUE, 0, WIN_X * WIN_Y * 3, a->mlx->img[0], 0, NULL, NULL))
//		printf("lol\n");
	clFinish(a->cl.command_queue);
	menu(a);
	refrash_clmem(&a->cl, &a->cl.mems[MEM_PIXEL_ID], CL_MEM_READ, 1);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
//	if (a->mrdw == 1 || a->keycode == K_A)
//		print_mini_frac(a);
	a->keycode = -1;
	a->done = 1;
}
