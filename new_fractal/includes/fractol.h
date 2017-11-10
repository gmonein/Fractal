#ifndef FRACTOL_H
# define FRACTOL_H
	
# define	WIN_H		1440
# define	WIN_W		2550

# include "libft.h"
# include "SDL.h"
# include "libcl.h"
# include <stdlib.h>
# include <unistd.h>
# include "shared_include.h"

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Cursor		*cursor;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
	uint32_t		*pixels;
	const Uint8		*key;
	int				run;
	t_cl			cl;
	t_fracarg		arg;
}					t_env;

#endif
