#ifndef SHARED_INCLUDE_H
# define SHARED_INCLUDE_H

typedef struct			s_fractal
{
	int					id;
	float				x1;
	float				x2;
	float				y1;
	float				y2;
	float				zoom;
	int					i_max;
	int					img_x;
	int					img_y;
	float				ci;
	float				c;
	float				pow;
	float				der;
	float				lim;
	float				zoom_i;
}						t_fractal;

typedef struct		s_fracarg
{
	float				c;
	float				ci;
	int					colors[16];
	t_fractal			fr;
}					t_fracarg;

#endif
