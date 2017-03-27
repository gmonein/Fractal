/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:11:05 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/26 22:50:48 by gmonein          ###   ########.fr       */
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

#define WIN_X 1024
#define WIN_Y 1024
#define IMGF_X 1024
#define IMGF_Y 1024
#define IMGF_MX 512
#define IMGF_MY 512
#define WINDOWS_NAME "gmonein's fractal"

typedef struct		s_cpx
{
	double		r;
	double		i;
}					t_cpx;

typedef struct		s_fractal
{
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	double		zoom;
	int			i_max;
	int			img_x;
	int			img_y;
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

typedef struct s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_all
{
	t_mlx		*mlx;
	t_fractal	*mdlb;
	t_point		mouse;
	double		zoom_i;
	long long	time;
	long long	micro;
	int			frame;
}				t_all;

t_mlx			*make_mlx(void);
int				ppx(int color, int x, int y, t_mlx *mlx);
int				**make_addr(t_mlx *mlx);
int				ft_rainbow(int i);
t_cpx			cpx_add(t_cpx a, t_cpx b);
t_cpx			cpx_mul(t_cpx a, t_cpx b);
void			mandelbrot(t_all *a);

#endif
