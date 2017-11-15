# include "shared_include.h"

#define DOUBLE_PRECISION (1)
typedef double2 cl_double_complex;
typedef float2 cl_float_complex;

#ifdef DOUBLE_PRECISION
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
typedef cl_double_complex cl_complex;
typedef double TYPE;
#else
typedef cl_float_complex cl_complex;
typedef float TYPE;
#endif
inline cl_complex cl_complex_multiply(const cl_complex* a, const cl_complex* b){
	return (cl_complex)(a->x*b->x - a->y*b->y,  a->x*b->y + a->y*b->x);
}

inline cl_complex cl_complex_pow(cl_complex a, cl_complex b)            \
{
	TYPE logr = log(hypot(a.x, a.y));
	TYPE logi = atan2(a.y, a.x);
	TYPE x = exp(logr * b.x - logi * b.y);
	TYPE y = logr * b.y + logi * b.x;

	TYPE cosy;
	TYPE siny = sincos(y, &cosy);
	return (cl_complex){x*cosy, x*siny};
}

inline cl_complex cl_complex_powr(cl_complex *a, TYPE b)
{
	TYPE logr = log(hypot(a->x, a->y));
	TYPE logi = atan2(a->y, a->x);
	TYPE x = exp(logr * b);
	TYPE y = logi * b;

	TYPE cosy;
	TYPE siny = sincos(y, &cosy);

	return (cl_complex){x * cosy, x*siny};
}

inline cl_complex cl_complex_ipow(const cl_complex* base ,  int exp ){
	cl_complex res;
	res.x=res.y=1;
	while(exp){
		if(exp & 1)
			res=cl_complex_multiply(&res,base);
		exp>>=1;
		res = cl_complex_multiply(&res,&res);
	}

	return res;
}

inline TYPE cl_complex_real_part(const cl_complex* n){
	return n->x;
}

inline TYPE cl_complex_imaginary_part(const cl_complex* n){
	return n->y;
}

inline TYPE cl_complex_modulus(const cl_complex* n){
	return (sqrt( (n->x*n->x)+(n->y*n->y) ));
}

inline cl_complex cl_complex_add(const cl_complex* a, const cl_complex* b){
	return (cl_complex)( a->x + b->x, a->y + b->y );
}

inline cl_complex cl_complex_divide(const cl_complex* a, const cl_complex* b){
	const  TYPE dividend = (b->x*b->x  + b->y*b->y);
	return (cl_complex)((a->x*b->x + a->y*b->y)/dividend , (a->y*b->x - a->x*b->y)/dividend);
}

inline TYPE cl_complex_argument(const cl_complex* a){
	if(a->x > 0){
		return atan(a->y / a->x);

	}else if(a->x < 0 && a->y >= 0){
		return atan(a->y / a->x) + M_PI;

	}else if(a->x < 0 && a->y < 0){
		return atan(a->y / a->x) - M_PI;

	}else if(a->x == 0 && a->y > 0){
		return M_PI/2;

	}else if(a->x == 0 && a->y < 0){
		return -M_PI/2;

	}else{
		return 0;
	}
}

inline cl_complex cl_complex_sqrt(const cl_complex* n){
	const TYPE sm = sqrt(cl_complex_modulus(n));
	const TYPE a2 = cl_complex_argument(n)/2;
	const TYPE ca2 = cos(a2);
	const TYPE sa2 = sin(a2);
	return (cl_complex)(sm * ca2 , sm * sa2);
}

inline cl_complex cl_complex_exp(const cl_complex* n){
	const TYPE e = exp(n->x);
	return (cl_complex)(e*cos(n->y) , e*sin(n->y));
}

inline cl_complex cl_complex_log(const cl_complex* z){
	return (cl_complex)( log(cl_complex_modulus(z)) , cl_complex_argument(z));
}

typedef struct			s_fr
{
	cl_complex			c;
	cl_complex			z;
	float				i;
	float				bi;
	cl_complex			h;
	cl_complex			z0;
	cl_complex			dz;
	float				smoothcolor;
}						t_fr;

int			ft_pal(float i, float i_max, __global int *pal, int p_max);
int			ft_pal(float i, float i_max, __global int *pal, int p_max)
{
	return (pal[(int)(i * p_max / i_max)]);
}

int			ft_gt_colors(int clr1, int clr2, double val)
{
	int		r;
	int		g;
	int		b;

	if (val > 1.0)
		val = 1.0;
	else if (val < 0.0)
		val = 0.0;
	r = floor((double)((clr1 >> 16) & 0xFF) -
			(((double)((clr1 >> 16) & 0xFF) - (double)((clr2 >> 16) & 0xFF)) * val));
	g = floor((double)((clr1 >> 8) & 0xFF) -
			(((double)((clr1 >> 8) & 0xFF) - (double)((clr2 >> 8) & 0xFF)) * val));
	b = floor((double)((clr1) & 0xFF) - (((double)((clr1) & 0xFF) \
					- (double)((clr2) & 0xFF)) * val));
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int			get_color(__global t_fractal *a, t_fr *t, __global int *color)
{
	cl_complex		d = t->z;
	t->i += 1.0f -
		log((
					log(d.x * d.x + d.y * d.y) * 0.50f)
				* DIVLOG) * DIVLOG;
	if (t->i < 0.0f)
		t->i = 0.0f;
	t->i *= 0.10f;
	if ((int)t->i < 0 || (int)t->i > 5)
		t->i = ((double)((int)((double)t->i * 1000000) % 5000000) / 1000000);
	return (ft_gt_colors(color[(int)t->i],
				color[(int)((int)t->i == 5 ? 0 : t->i + 1)],
				(double)(t->i - (int)t->i)));
}


__kernel void		mandelbrot(__global int *pixels, __global t_fractal *args, __global int *pal)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			off_x = get_global_offset(0);
	int			off_y = get_global_offset(1);

	t_fr		v;
	cl_complex	bz;
	cl_complex	cz;
	size_t		i_max = args->i_max;
	double		zoom = args->zoom;
	double		power = args->pow;

	v.z.x = 0;//args->c;
	v.z.y = 0;//args->ci;
	v.i = 0;
	v.c.x = (double)(x - off_x) / zoom + args->x1;
	v.c.y = (double)(y - off_y)/ zoom + args->y1;
	while (v.z.x * v.z.x + v.z.y * v.z.y < 1 << 8 && v.i < i_max)
	{
		bz = v.z;
		for (int i = 0; i < power; i++)
		{
			cz = v.z;
			v.z.x = v.z.x * cz.x - v.z.y * cz.y;
			v.z.y = cz.x * cz.y * 2;
		}
		v.z += v.c;
		v.i++;
	}
	if (args->smooth == 0)
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : pal[(int)v.i % 6];
	else
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : get_color(args, &v, pal);
}

__kernel void		julia(__global int *pixels, __global t_fractal *args, __global int *pal)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			off_x = get_global_offset(0);
	int			off_y = get_global_offset(1);

	t_fr		v;
	cl_complex	bz;
	size_t		i_max = args->i_max;
	double		zoom = args->zoom;

	v.c.x = args->c;
	v.c.y = args->ci;
	v.i = 0;
	v.z.x = (double)(x - off_x) / zoom + args->x1;
	v.z.y = (double)(y - off_y) / zoom + args->y1;
	while (v.z.x * v.z.x + v.z.y * v.z.y < 16 && v.i < i_max)
	{
		bz = v.z;
		v.z.x = bz.x * bz.x - bz.y * bz.y;
		v.z.y = bz.x * bz.y * 2;
		v.z += v.c;
		v.i++;
	}
	if (args->smooth == 0)
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : pal[(int)v.i % 6];
	else
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : get_color(args, &v, pal);
}

__kernel void		turtle(__global int *pixels, __global t_fractal *args, __global int *pal)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			off_x = get_global_offset(0);
	int			off_y = get_global_offset(1);

	t_fr		v;
	cl_complex	bz;
	size_t		i_max = args->i_max;
	double		zoom = args->zoom;

	v.c.x = args->c;
	v.c.y = args->ci;
	v.i = 0;
	v.z.x = (double)(x - off_x) / zoom + args->x1;
	v.z.y = (double)(y - off_y) / zoom + args->y1;
	while (v.z.x * v.z.x + v.z.y * v.z.y < 16 && v.i < i_max)
	{
		bz = v.z;
		v.z = cl_complex_ipow(&v.z, 3);
		/*		v.z = cl_complex_multiply(&v.z, &v.z);
				v.z = cl_complex_multiply(&v.z, &v.z);
				v.z = cl_complex_multiply(&bz, &v.z);
				*/	//	v.z.x = bz.x * bz.x - bz.y * bz.y;
		//	v.z.y = bz.x * bz.y * 2;
		v.z += v.c;
		v.i++;
	}
	if (args->smooth == 0)
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : pal[(int)v.i % 6];
	else
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : get_color(args, &v, pal);
}

__kernel void		island(__global int *pixels, __global t_fractal *args, __global int *pal)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			off_x = get_global_offset(0);
	int			off_y = get_global_offset(1);

	t_fr		v;
	cl_complex	bz;
	cl_complex	buf1;
	cl_complex	buf2;
	cl_complex	buf3;
	size_t		i_max = args->i_max;
	double		zoom = args->zoom;

	v.c.x = args->c;
	v.c.y = args->ci;
	v.i = 0;
	v.z.x = (double)(x - off_x) / zoom + args->x1;
	v.z.y = (double)(y - off_y) / zoom + args->y1;
	while (v.z.x * v.z.x + v.z.y * v.z.y < 16 && v.i < i_max)
	{
		bz = v.z;
		buf1 = cl_complex_multiply(&bz, &bz) - bz;
		buf2 = bz + v.c;

		v.z = cl_complex_multiply(&buf1, &buf1);
		buf3 = cl_complex_multiply(&buf2, &buf2);
		v.z += cl_complex_multiply(&buf3, &buf3);
		v.i++;
	}
	if (args->smooth == 0)
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : pal[(int)v.i % 6];
	else
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : get_color(args, &v, pal);
}

__kernel void		newton(__global int *pixels, __global t_fractal *args, __global int *pal)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			off_x = get_global_offset(0);
	int			off_y = get_global_offset(1);

	t_fr		v;
	cl_complex	buf1;
	cl_complex	buf2;
	cl_complex	buf3;
	size_t		i_max = args->i_max;
	double		zoom = args->zoom;
	double		lim = args->lim;

	v.h.x = args->der;
	v.h.y = args->der;
	v.i = 0;
	v.z.x = (double)(x - off_x) / zoom + args->x1;
	v.z.y = (double)(y - off_y)/ zoom + args->y1;
	while (v.i < i_max)
	{
		buf1 = v.h + v.z;
		buf2 = cl_complex_multiply(&buf1, &buf1);
		buf2 = cl_complex_multiply(&buf1, &buf2);
		buf2 -= 1.0f;
		buf1 = v.z;
		buf3 = cl_complex_multiply(&buf1, &buf1);
		buf3 = cl_complex_multiply(&buf1, &buf3);
		buf3 -= 1.0f;
		v.dz = buf1 - buf3;
		v.dz = cl_complex_divide(&v.dz, &v.h);
		v.z0 = v.z - buf3;
		v.z0 = cl_complex_divide(&v.z0, &v.dz);
		buf3 = v.z0 - v.z;
		v.z = cl_complex_multiply(&v.z0, &v.z0);
		if (cl_complex_modulus(&buf3) < lim)
			break ;
		v.i++;
	}
	if (args->smooth == 0)
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : pal[(int)v.i % 6];
	else
		pixels[x + y * WIN_X] = v.i == i_max ? 0 : get_color(args, &v, pal);
}
