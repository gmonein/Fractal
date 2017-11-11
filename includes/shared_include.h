#ifndef SHARED_INCLUDE_H
# define SHARED_INCLUDE_H
# define WIN_X 2560
# define WIN_Y 1440
# define IMGF_X WIN_X
# define IMGF_Y WIN_Y
# define M_IMGF_X 256
# define M_IMGF_Y 100
# define IMGF_MX 512
# define IMGF_MY 512
# define DIVLOG 1.44269504088896338700465094007086008787155151367187500000000000
# define PI 3.14159265359

typedef struct			s_fractal
{
	int					id;
	double				x1;
	double				x2;
	double				y1;
	double				y2;
	double				zoom;
	int					i_max;
	int					img_x;
	int					img_y;
	double				ci;
	double				c;
	double				pow;
	double				der;
	double				lim;
	double				zoom_i;
	int					smooth;
}						t_fractal;

typedef struct		s_fracarg
{
	double				c;
	double				ci;
	int					colors[16];
	t_fractal			fr;
}					t_fracarg;

#endif
