/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:11:05 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/25 19:07:31 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H_
# define FRACTAL_H_

#include <stdio.h>
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>

#define WIN_X 1024
#define WIN_Y 1024
#define IMGF_X 1024
#define IMGF_Y 1024
#define WINDOWS_NAME "gmonein's fractal"

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

typedef struct s_all
{
	t_mlx		*mlx;
	int			i_max;
}				t_all;

#endif
