/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:11:05 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 01:08:37 by gmonein          ###   ########.fr       */
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

#define DIVLOG 1.44269504088896338700465094007086008787155151367187500000000000
#define WIN_X 1024
#define WIN_Y 924
#define IMGF_X 1024
#define IMGF_Y 724
#define M_IMGF_X 256
#define M_IMGF_Y 100
#define IMGF_MX 512
#define IMGF_MY 512
#define PI 3.14159265359
#define WINDOWS_NAME "gmonein's fractal"
#define N_MDLB "Mandelbrot"
#define N_PDLB "Powdelbrot"
#define N_JUL "Julia"
#define N_PJUL "Powlia"
#define N_NWTN "Newton"
#define N_RSCE "Rosace"
#define N_TRTL "Turtle"
#define N_ISLD "Island"
typedef unsigned long long	t_ullong;
typedef _Complex double	t_complex;

#define ID_MDLB 1
#define ID_PDLB 2
#define ID_JUL 3
#define ID_PJUL 4
#define ID_NWTN 5
#define ID_RSCE 6
#define ID_TRTL 7
#define ID_ISLD 8

typedef struct	s_fr
{
	t_complex		c;
	t_complex		z;
	double			i;
	double			bi;
	t_complex		h;
	t_complex		z0;
	t_complex		dz;
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
	int				id;
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
	double			pow;
	double			der;
	double			lim;
	t_ullong		zoom_i;
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
	int			x;
	int			y;
}				t_point;

typedef struct s_all
{
	t_mlx		*mlx;
	t_mlx		mini_mlx;
	t_fractal	mdlb;
	t_fractal	pdlb;
	t_fractal	jul;
	t_fractal	pjul;
	t_fractal	nwtn;
	t_fractal	rsce;
	t_fractal	trtl;
	t_fractal	jlnw;
	t_fractal	other;
	t_fractal	*act;
	t_point		mouse;
	int			keycode;
	int			mrdw;
	int			colors[4][16];
	void		(*frac)(struct s_all *, t_square, t_fr *);
	int			pal;
	int			p_max;
	int			smooth;
	int			thread_cnt;
	float		pow_i;

	double		i_inc;
	int			done;
	int			redraw;
	int			block;
	double		c;
	double		ci;
	t_o_thread	**thread;
}				t_all;

void			ft_putstr_fd(const char *str, int fd);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_pal(double i, double i_max, int *pal, int p_max);
int				ft_gt_colors(int clr1, int clr2, double val);
int				get_color(t_all *a, t_fr *t, int i_max);
int				ft_rand(int min, int max);
t_mlx			*make_mlx(void);
t_o_thread		**malloc_thread(int count);
void			create_thread(t_all *a, t_o_thread **thread, int count);
void			*thread_fonc(void *b);
int				ppx(int color, int x, int y, t_mlx *mlx);
int				**make_addr(t_mlx *mlx);
int				ft_rainbow(int i);
t_cpx			cpx_add(t_cpx a, t_cpx b);
t_cpx			cpx_mul(t_cpx a, t_cpx b);
t_o_thread		**malloc_thread(int count);
void			redraw(t_all *a);
void			fractal(t_all *a, t_square b);
void			mandelbrot(t_all *a, t_square b, t_fr *v);
void			julia(t_all *a, t_square b, t_fr *v);
void			newton(t_all *a, t_square b, t_fr *v);
void			rosace(t_all *a, t_square b, t_fr *v);
void			powdelbrot(t_all *a, t_square b, t_fr *v);
void			pow_julia(t_all *a, t_square b, t_fr *v);
void			turtle(t_all *a, t_square b, t_fr *v);
void			jul_new(t_all *a, t_square b, t_fr *v);
t_mlx			make_mini_mlx(t_all *a);
void			print_mini_frac(t_all *a);
void			zoom_in(int x, int y, int i, t_all *a);
void			zoom_out(int x, int y, int i, t_all *a);

#endif
