/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:32:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/14 06:36:16 by gmonein          ###   ########.fr       */
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
	double		zoom = LEFT_MENU / 3.2;
	void		*b1;
	int			pos = 0;
	int			size_y = WIN_Y / 4;

	a->cl.mems[MEM_ARG_ID].ptr = &a->other;
	a->other = (t_fractal){ ID_JUL, -1.7f, -0.4f, -1.1f, 1.2f, zoom, a->jul.i_max,
		(0.6f + 2.1f) * zoom, (2.4f) * zoom, a->jul.c, a->jul.ci, 0, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_JULIA_ID], (size_t[3]){WIN_X - LEFT_MENU, size_y * pos, 0}, (size_t[3]){LEFT_MENU, size_y, 0});

	pos++;
	a->other = (t_fractal){ ID_JUL, -1.7f, 0.0f, -1.0f, 1.2f, zoom, a->trtl.i_max,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, a->trtl.c, a->trtl.ci, 0, 0
		, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_TURTLE_ID], (size_t[3]){WIN_X - LEFT_MENU, size_y * pos, 0}, (size_t[3]){LEFT_MENU, size_y, 0});

	pos++;
	a->other = (t_fractal){ ID_JUL, -1.0f, 0.0f, -1.0f, 1.2f, zoom, a->jlnw.i_max,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, a->jlnw.c, a->jlnw.ci,
		0, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_ISLAND_ID], (size_t[3]){WIN_X - LEFT_MENU, size_y * pos, 0}, (size_t[3]){LEFT_MENU, size_y, 0});

	pos++;
	a->other = (t_fractal){ ID_MDLB, -2.4f, 0.0f, -1.0f, 1.2f, zoom, a->mdlb.i_max,
		(0.6f + 2.1f) * zoom, (1.2f + 1.2f) * zoom, 0, 0, 1, 0, 0, 0, 1};
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 1);
	draw_frac(a, a->cl.kernels[KRN_MDLB_ID], (size_t[3]){WIN_X - LEFT_MENU, size_y * pos, 0}, (size_t[3]){LEFT_MENU, size_y, 0});
	clFinish(a->cl.command_queue);
}
double clockToMilliseconds(clock_t ticks)
{
    return (ticks * 1000/(double)CLOCKS_PER_SEC);
}
int				redraw(t_all *a)
{
	int		i;
	void	*ret;
	clock_t		begin_frame;
	clock_t		end_frame;
	clock_t		delta_time;
	char		buf[64];
	char		buf2[64];

	i = -1;
	clFinish(a->cl.command_queue);
	if (a->done)
		return (0);
	begin_frame = clock();
	a->cl.mems[MEM_ARG_ID].ptr = a->act;
	refrash_clmem(&a->cl, &a->cl.mems[MEM_ARG_ID], CL_MEM_WRITE, 0);
	a->cl.mems[MEM_OARG_ID].ptr = &a->colors[a->pal];
	refrash_clmem(&a->cl, &a->cl.mems[MEM_OARG_ID], CL_MEM_WRITE, 0);
	cl_run(&a->cl, a->kfrac);
	clFinish(a->cl.command_queue);
	menu(a);
	clFinish(a->cl.command_queue);
	refrash_clmem(&a->cl, &a->cl.mems[MEM_PIXEL_ID], CL_MEM_READ, 1);
	mlx_put_image_to_window(a->mlx->mlx, a->mlx->win, a->mlx->image, 0, 0);
	end_frame = clock();
	delta_time = end_frame - begin_frame;
	a->i_max = a->act->i_max;
	a->render_time = (double)delta_time * 1000 / CLOCKS_PER_SEC;//clockToMilliseconds(delta_time);
	a->fps = 1000 / a->render_time;
	snprintf(buf, sizeof(buf), "%d", a->fps);
	strcpy(buf2, "Fps : ");
	strcat(buf2, buf);
	mlx_string_put(a->mlx->mlx, a->mlx->win, 10, 5, 0xFFFFFF, buf2);
	snprintf(buf, sizeof(buf), "%lf", a->render_time);
	strcpy(buf2, "Render time : ");
	strcat(buf2, buf);
	strcat(buf2, " ms");
	mlx_string_put(a->mlx->mlx, a->mlx->win, 10, 25, 0xFFFFFF, buf2);
	snprintf(buf, sizeof(buf), "%d", a->i_max);
	strcpy(buf2, "Iterations : ");
	strcat(buf2, buf);
	mlx_string_put(a->mlx->mlx, a->mlx->win, 10, 40, 0xFFFFFF, buf2);
	a->keycode = -1;
	a->done = 1;
	return (0);
}
