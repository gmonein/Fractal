# include "shared_include.h"

#define DOUBLE_PRECISION (0)

typedef double2 cl_double_complex;
typedef float2 cl_float_complex;

#ifdef DOUBLE_PRECISION
typedef cl_double_complex cl_complex;
typedef double TYPE;
#else
typedef cl_float_complex cl_complex;
typedef float TYPE;
#endif

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

inline cl_complex cl_complex_multiply(const cl_complex* a, const cl_complex* b){
	return (cl_complex)(a->x*b->x - a->y*b->y,  a->x*b->y + a->y*b->x);
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

int			ft_pal(float i, float i_max, int *pal, int p_max)
{
	return (pal[(int)(i * p_max / i_max)]);
}
/*
int			get_color(t_fr *t)
{
	t->i += 1.0f -
	log((log(creal(t->z) * creal(t->z) + cimag(t->z) * cimag(t->z)) * 0.50f)
		* DIVLOG) * DIVLOG;
	if (t->i < 0.0f)
		t->i = 0.0f;
	t->i *= 0.10f;
	if ((int)t->i < 0 || (int)t->i > 5)
		t->i = ((double)((int)((double)t->i * 1000000) % 5000000) / 1000000);
	return (ft_gt_colors(a->colors[a->pal][(int)t->i],
	a->colors[a->pal][(int)((int)t->i == 5 ? 0 : t->i + 1)],
	(double)(t->i - (int)t->i)));
}
*/
__kernel void		core(__global int *pixels, __global t_fractal *args)
{
	int			x = get_global_id(0);
	int			y = get_global_id(1);
	int			size_x = get_global_size(0);
	int			size_y = get_global_size(1);

	float		zoom = args->zoom;
	float		x1 = args->x1;
	float		x2 = args->x2;
	float		y1 = args->y1;
	float		y2 = args->y2;
	int			i_max = args->i_max;
	float		lim = args->lim;
	float		der = args->der;

	t_fr		v;

	v.h.x = der;
	v.h.y = der;
	v.i = 0;
	v.z = x1 / zoom + x1 + (y1 / zoom + y1) * I;
	while (v.i < i_max)
	{
		v.dz = (fn(v.z + v.h) - fn(v.z)) / v.h;
		v.z0 = v.z - fn(v.z) / v.dz;
		v.i++;
		if (cabs(v.z0 - v.z) < lim)
			break ;
		v.z = v.z0;
	}
	pixels[x + y * size_x] = (v.i == i_max ?
		0x0 : ft_pal(v.i, i_max, args->colors, 16));
}
