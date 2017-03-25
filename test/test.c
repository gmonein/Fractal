/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:09:43 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/25 19:07:29 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int			ppx(int color, int x, int y, t_mlx *mlx)
{
	if (x < 0 || y < 0 || x > IMGF_X || y > IMGF_Y)
		return (-1);
	mlx->img[y][x] = color;
	return (1);
}

int			**make_addr(t_mlx *mlx)
{
	int		**img;
	int		i;
	int		steps;

	i = 0;
	steps = IMGF_Y;
	img = (int **)malloc(sizeof(int *) * (IMGF_Y + 1));
	img[0] = (int *)mlx->addr;
	while (++i < steps)
		img[i] = (int *)&mlx->addr[i * IMGF_X * 4];
	img[i] = NULL;
	return (img);
}

t_mlx		*make_mlx(void)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, WINDOWS_NAME);
	mlx->image = mlx_new_image(mlx->mlx, IMGF_X, IMGF_Y);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bpp, &mlx->line_size,
																&mlx->edian);
	mlx->img = make_addr(mlx);
	return (mlx);
}

void		mandelbrot(t_all *a)
{
int y = -1;
int x = 0;
double x1 = -2.1;
double x2 = 0.6;
double y1 = -1.2;
double y2 = 1.2;
int zoom = 200;
int iteration_max = 50;
double tmp;
double i;
double image_x = (x2 - x1) * zoom;
double image_y = (y2 - y1) * zoom;

while (++y > -1 && y < image_y && (x = -1) == -1)
	while (++x > -1 && x < image_x)
	{
        double c_r = x / zoom + x1;
        double c_i = y / zoom + y1;
        double z_r = 0;
        double z_i = 0;
        i = 0;
        while (z_r * z_r + z_i * z_i < 4 && i < 50)
		{
            tmp = z_r;
            z_r = z_r * z_r - z_i * z_i + c_r;
            z_i = 2 * z_i * tmp + c_i;
            i = i + 1;
		}
        if (i == 50)
			ppx(0x00FFFFFF, x, y, a->mlx);
        else
			ppx(i * 255, x, y, a->mlx);
	}
}

int			main(int argc, char **argv)
{
	t_all	a;

	a.mlx = make_mlx();
	mandelbrot(&a);
	mlx_put_image_to_window(a.mlx->mlx, a.mlx->win, a.mlx->image, 0, 0);
	return (mlx_loop(a.mlx->mlx));
}
