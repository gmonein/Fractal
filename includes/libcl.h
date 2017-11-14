
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeg <jpeg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:42:05 by jpeg              #+#    #+#             */
/*   Updated: 2017/11/10 15:50:29 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_CL_H
# define EASY_CL_H

#ifdef __APPLE__
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif

# define LEFT_MENU			WIN_X / 5

# define ERR_CL				42
# define MINI_FRAC_H		400

# define MAX_SOURCE_SIZE	30000
# define MAX_ERR_LOG		(10000)
# define MAX_KERNEL_ARGS	5
# define WORK_DIM			2

# define CL_MEM_DESTROY		1
# define CL_MEM_CREATE		2
# define CL_MEM_RECREATE	3
# define CL_MEM_WRITE		4
# define CL_MEM_READ		8

# define MEM_PIXEL_ID		0
# define MEM_ARG_ID			1
# define MEM_OARG_ID		2
# define NB_MEM				3

# define KRN_JULIA_ID			0
# define KRN_MDLB_ID			1
# define KRN_TURTLE_ID			2
# define KRN_ISLAND_ID			3
# define KRN_NEWTON_ID			4
# define NB_KRN					5

# define KRN_NAME			"julia"
# define KRN_NBSOURCE		1
# define KRN_SRCPATH		(char*[]){"sources/fractol.cl"}
# define KRN_NBARG			3
# define KRN_MEMARG			(int[]){MEM_PIXEL_ID, MEM_ARG_ID, MEM_OARG_ID}
# define KRN_CMPFLG			"-I includes"
# define KRN_WRKDIM			2
# define KRN_GWRKSIZE		(size_t[3]){WIN_X - LEFT_MENU, WIN_Y, 0}
# define KRN_LWRKSIZE		(size_t[3]){1, 0, 0}

typedef struct				s_kernel_init
{
	char					*name;
	char					nbsource;
	char					**sources;
	char					nb_arg;
	int						*args;
	char					*comp_flags;
	char					work_dim;
	size_t					*global_worksize;
	size_t					*local_worksize;
}							t_kernel_init;

typedef struct			s_clmem
{
	void				*ptr;
	size_t				arg_size;
	size_t				mem_size;
	cl_mem_flags		flag;
	cl_mem				mem;
	void				*map;
}						t_clmem;

typedef struct			s_arg
{
	void				*ptr;
	size_t				mem_size;
	size_t				arg_size;
	cl_mem_flags		flag;
}						t_arg;

typedef struct			s_clkernel
{
	cl_kernel			kernel;
	char				*name;
	cl_program			program;
	t_clmem				*args[MAX_KERNEL_ARGS];
	char				nb_arg;
	char				work_dim;
	size_t				global_worksize[3];
	size_t				local_worksize[3];
	size_t				offset[3];
}						t_clkernel;

typedef struct			s_cl
{
	cl_context			context;
	cl_command_queue	command_queue;
    cl_platform_id		platform_id[10];
	cl_device_id		device_id[10];
    cl_uint				ret_num_devices;
    cl_uint				ret_num_platforms;
	t_clkernel			kernels[10];
	t_clmem				mems[10];
	size_t				nb_mems;
	size_t				nb_kernel;
	size_t				nb_event;
	cl_event			*event;
}						t_cl;

// CL FUNCTIONS

cl_event				cl_run(t_cl *cl, t_clkernel *kernel);
void					cl_end(t_cl *cl);
void					refrash_clmem(t_cl *cl, t_clmem *mem, char todo, cl_int wait);

/*
** ********************************** errors ***********************************
*/

void			refrash_clmem(t_cl *cl, t_clmem *mem, char todo, cl_int wait);
#endif
