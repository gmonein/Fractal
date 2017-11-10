# include "fractol.h"

void		redraw(t_env *env)
{
	cl_run(&env->cl, &env->cl.kernels[KRN_RT_ID]);
	refrash_clmem(&env->cl, &env->cl.mems[MEM_PIXEL_ID], CL_MEM_READ, 0);
}

void		handle_events(t_env *env)
{

}

static int	global_loop(t_env *env)
{
	env->run = 1;
	env->key = SDL_GetKeyboardState(NULL);
	while (env->run)
	{
		SDL_PollEvent(&env->event);
		if (env->event.type == 256)
			env->run = 0;
		if (env->event.type == SDL_WINDOWEVENT &&
				(env->event.window.type == SDL_WINDOWEVENT_CLOSE
				|| env->event.key.keysym.sym == SDLK_ESCAPE
				|| env->event.type == SDL_QUIT))

		handle_events(env);
		redraw(env);

		SDL_UpdateTexture(env->texture, NULL, env->pixels, WIN_W * sizeof(int));
		SDL_RenderCopy(env->render, env->texture, NULL, NULL);
		SDL_RenderPresent(env->render);
	}
	return (0);
}


void				cl_init(t_env *env);
int			init_opencl(t_env *env)
{
	cl_init(env);
	return (1);
}

int			init_sdl(t_env *env)
{
	if (SDL_Init(SDL_INIT_EVENTS) == -1)
		return (0);
	if (!(env->win = SDL_CreateWindow("Wolf3D", 0, 0, WIN_W, WIN_H, 0)))
		return (0);
	env->render = SDL_CreateRenderer(env->win, 0,
			SDL_RENDERER_TARGETTEXTURE
			| SDL_RENDERER_SOFTWARE
			| SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(env->render, 0xC0, 0, 0, 255);
	SDL_RenderClear(env->render);
	SDL_RenderPresent(env->render);
	if (!(env->pixels = (uint32_t *)malloc(sizeof(uint32_t) * (WIN_H * WIN_W))))
		return (0);
	if (!(env->texture = SDL_CreateTexture(env->render,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					WIN_W, WIN_H)))
		return (0);
	SDL_SetRenderTarget(env->render, env->texture);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env		env;

	if (!init_sdl(&env))
		return (EXIT_FAILURE);
	if (!init_opencl(&env))
		return (EXIT_FAILURE);
	return (global_loop(&env));
}
