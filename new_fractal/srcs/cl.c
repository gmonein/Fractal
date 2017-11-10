# include "fractol.h"

void							errors(int e, char *error)
{
	ft_putstr(error);
	ft_putstr("\n");
	exit(1);
}

static inline void				cl_get_context(t_cl *cl)
{
	cl_int		ret;

	if (clGetPlatformIDs(3, cl->platform_id, &cl->ret_num_platforms))
		errors(ERR_CL, "clGetPlatformIDfailure --");
	if (clGetDeviceIDs(cl->platform_id[0], CL_DEVICE_TYPE_GPU, 1,
						cl->device_id, &cl->ret_num_devices))
		errors(ERR_CL, "clGetDeviceIDs failure --");
	cl->context = clCreateContext(NULL, 1, cl->device_id, NULL, NULL, &ret);
	ret ? errors(ERR_CL, "clCreateContext failure --") : 0;
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id[0], 0, &ret);
	ret ? errors(ERR_CL, "clCreateCommandQueue failure --") : 0;
}

char			**read_from_paths(char **paths, char nbpath)
{
	FILE	*fp;
	char	*kernel_str;
	char	**res;
	char	*line;
	int		i;

	res = (char **)malloc(sizeof(char *) * (nbpath + 1));
	line = (char *)malloc(sizeof(char) * nbpath * MAX_SOURCE_SIZE);
	bzero(line, sizeof(char) * nbpath * MAX_SOURCE_SIZE);
	res[nbpath] = NULL;
	i = -1;
	while (++i < nbpath)
	{
		res[i] = &line[i * MAX_SOURCE_SIZE];
		fp = fopen(paths[i], "r");
		res[i][fread(res[i], 1, MAX_SOURCE_SIZE, fp)] = '\0';
		fclose(fp);
	}
	return (res);
}

void			compilation_error(cl_program program, void *cl)
{
	char		buf[MAX_ERR_LOG];

	clGetProgramBuildInfo(program, ((t_cl *)cl)->device_id[0],
			CL_PROGRAM_BUILD_LOG, MAX_ERR_LOG, &buf, NULL);
	write(1, buf, strlen(buf));
}

void			cl_create_kernel(t_cl *cl, t_clkernel *dst, t_kernel_init *init)
{
	cl_int		ret;
	char		**sources;
	int			i;

	sources = read_from_paths(init->sources, init->nbsource);
	dst->program = clCreateProgramWithSource(cl->context,
							init->nbsource, (const char **)sources, NULL, &ret);
	free(sources[0]);
	free(sources);
	ret ? errors(ERR_CL, "clCreateProgramWithSource failure --") : 0;
    ret = clBuildProgram(dst->program, cl->ret_num_devices, cl->device_id,
							init->comp_flags, compilation_error, cl);
	ret ? errors(ERR_CL, "clBuildProgram failure --") : 0;
    dst->kernel = clCreateKernel(dst->program, init->name, &ret);
	ret ? errors(ERR_CL, "clCreateKernel failure --") : 0;
	i = -1;
	while (++i < init->nb_arg)
	{
		dst->args[i] = &cl->mems[init->args[i]];
		if(clSetKernelArg(dst->kernel, i,
			dst->args[i]->arg_size, &dst->args[i]->mem))
			errors(ERR_CL, "clSetKernelArg failure --");
	}
	dst->name = init->name;
	dst->nb_arg = init->nb_arg;
	dst->work_dim = init->work_dim;
	memcpy(dst->global_worksize, init->global_worksize, sizeof(size_t) * 3);
	memcpy(dst->local_worksize, init->local_worksize, sizeof(size_t) * 3);
}

void			refrash_clmem(t_cl *cl, t_clmem *mem, char todo, cl_int wait)
{
	cl_int		ret;
	if (todo & CL_MEM_DESTROY)
	{
		clEnqueueUnmapMemObject(cl->command_queue, mem->mem, mem->map, 0, 0, 0);
		if (clReleaseMemObject(mem->mem))
			errors(ERR_CL, "clReleaseMemObject failure --");
	}
	if (todo & CL_MEM_CREATE)
	{
		mem->mem = clCreateBuffer(cl->context,
						mem->flag, mem->mem_size, NULL, &ret);
		ret ? errors(ERR_CL, "clCreateBuffer failure --") : 0;
//		mem->map = clEnqueueMapBuffer(cl->command_queue, mem->mem, CL_TRUE, 0, 0, 0, 0, 0, 0, 0);
	}
	if (todo & CL_MEM_WRITE)
		if (clEnqueueWriteBuffer(cl->command_queue, mem->mem,
						wait, 0, mem->mem_size, mem->ptr,
															0, NULL, NULL))
			errors(ERR_CL, "clEnqueueWriteBuffer failure --");
	if (todo & CL_MEM_READ)
		if (clEnqueueReadBuffer(cl->command_queue, mem->mem,
			wait, 0, mem->mem_size, mem->ptr, 0, NULL, NULL))
			errors(ERR_CL, "clEnqueueReadBuffer failure --");
}

void		init_clmem(t_cl *cl, t_env *env)
{
	int		i;

	cl->nb_mems = NB_MEM;
	cl->mems[MEM_PIXEL_ID] = (t_clmem){
		env->pixels,
		sizeof(cl_mem),
		sizeof(uint32_t) * WIN_H * WIN_W,
		CL_MEM_WRITE_ONLY,
		0,
		NULL
	};
	cl->mems[MEM_ARG_ID] = (t_clmem){
		&env->arg,
		sizeof(cl_mem),
		sizeof(t_arg),
		CL_MEM_READ_ONLY,
		0,
		NULL
	};
	i = -1;
	while (++i < NB_MEM)
		refrash_clmem(cl, &cl->mems[i], CL_MEM_CREATE, CL_FALSE);
}

void				cl_init(t_env *env)
{
	bzero(&env->cl, sizeof(t_cl));
	cl_get_context(&env->cl);
	init_clmem(&env->cl, env);
	cl_create_kernel(&env->cl, &env->cl.kernels[KRN_RT_ID],
						&(t_kernel_init){KRN_NAME,
									KRN_NBSOURCE,
									KRN_SRCPATH,
									KRN_NBARG,
									KRN_MEMARG,
									KRN_CMPFLG,
									KRN_WRKDIM,
									KRN_GWRKSIZE,
									KRN_LWRKSIZE}
	);
}

cl_event			cl_run(t_cl *cl, t_clkernel *kernel)
{
	int		ret;
	cl_event event;

	if ((ret = clEnqueueNDRangeKernel(cl->command_queue, kernel->kernel,
		kernel->work_dim, kernel->offset,
		kernel->global_worksize, NULL, cl->nb_event, cl->event, &event)))
			errors(ERR_CL, "clEnqueueNDRangeKernel failure --");
	return (event);
}

void				cl_end(t_cl *cl)
{
	int			i;
	cl_int		ret;

    ret = clFlush(cl->command_queue);
    ret = clFinish(cl->command_queue);
	i = -1;
	while (++i < cl->nb_kernel)
	{
		ret = clReleaseKernel(cl->kernels[i].kernel);
		ret = clReleaseProgram(cl->kernels[i].program);
	}
	i = -1;
	while (++i < cl->nb_mems)
		ret = clReleaseMemObject(cl->mems[i].mem);
    ret = clReleaseCommandQueue(cl->command_queue);
    ret = clReleaseContext(cl->context);
}
