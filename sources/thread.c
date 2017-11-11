/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:32:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/11 21:58:20 by gmonein          ###   ########.fr       */
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
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	a->cl.mems[MEM_OARG_ID].ptr = &a->colors[a->pal];
	refrash_clmem(&a->cl, &a->cl.mems[MEM_OARG_ID], CL_MEM_WRITE, 1);
	cl_run(&a->cl, a->kfrac);
//	clFinish(a->cl.command_queue);
	if (clEnqueueReadBuffer(a->cl.command_queue, a->cl.mems[MEM_PIXEL_ID].mem,
		CL_TRUE, 0, WIN_X * WIN_Y * 3, a->mlx->img[0], 0, NULL, NULL))
		printf("lol\n");
//	clFinish(a->cl.command_queue);
	refrash_clmem(&a->cl, &a->cl.mems[MEM_PIXEL_ID], CL_MEM_READ, 1);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
//	if (a->mrdw == 1 || a->keycode == K_A)
//		print_mini_frac(a);
	a->keycode = -1;
	a->done = 1;
}
