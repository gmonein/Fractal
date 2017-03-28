/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:11:05 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 22:36:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H_
# define FRACTAL_H_

#include "macos_keycode.h"
#include <stdio.h>
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "time.h"
#include <pthread.h>

#define WIN_X 1024
#define WIN_Y 1024
#define IMGF_X 1024
#define IMGF_Y 724
#define IMGF_MX 512
#define IMGF_MY 512
#define PI 3.1415
#define WINDOWS_NAME "gmonein's fractal"

typedef struct	s_fr
{
	double complex c;
	double complex z;
	int				i;
	double			smoothcolor;
}				t_fr;

typedef struct		s_cpx
{
	double		r;
	double		i;
}					t_cpx;

typedef struct		s_square
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}					t_square;

typedef struct		s_fractal
{
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			zoom;
	int				i_max;
	int				img_x;
	int				img_y;
	double			ci;
	double			c;
	float			pow;
}					t_fractal;

typedef struct	s_mlx
{
	void		*win;
	void		*mlx;
	void		*image;
	char		*addr;
	int			line_size;
	int			edian;
	int			bpp;
	int			**img;
}				t_mlx;

typedef struct	s_o_thread
{
	pthread_t			thread;
	int					id;
	struct s_all		*all;
	t_square			zone;
}				t_o_thread;

typedef struct s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_all
{
	t_mlx		*mlx;
	t_fractal	*mdlb;
	t_fractal	*julia;
	t_point		mouse;
	void		(*frac)(struct s_all *, t_square, t_fr *);
	double		zoom_i;
	int			frame;
	int			thread_cnt;
	float		pow_i;

	int			i_inc;
	int			done;
	int					redraw;
	int					quit;
	t_o_thread			**thread;
}				t_all;

t_mlx			*make_mlx(void);
int				ppx(int color, int x, int y, t_mlx *mlx);
int				**make_addr(t_mlx *mlx);
int				ft_rainbow(int i);
t_cpx			cpx_add(t_cpx a, t_cpx b);
t_cpx			cpx_mul(t_cpx a, t_cpx b);
void			mandelbrot(t_all *a, t_square b, t_fr *v);
void			julia(t_all *a, t_square b, t_fr *v);

void		fractal(t_all *a, t_square b);
#endif
