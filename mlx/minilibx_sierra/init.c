/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:10:18 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 04:47:10 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    make_p_map(t_p *p)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	p->p_map = (t_i_point ***)malloc(sizeof(t_i_point **) * p->img_y);
	p->p_map[0] = (t_i_point **)malloc(sizeof(t_i_point *) * p->img_y * p->img_x);
	while (i <= p->img_y)
	{
		p->p_map[i] = &p->p_map[0][j];
		j += p->img_x;
		i++;
	}
}

void	clear_p_map(t_p *p)
{
	int		i;
	int		end;

	end = p->img_x * p->img_y;
	i = 0;
	while (i < end)
	{
		p->p_map[0][i] = NULL;
		p->p_map[0][i + 1] = NULL;
		p->p_map[0][i + 2] = NULL;
		p->p_map[0][i + 3] = NULL;
		p->p_map[0][i + 4] = NULL;
		p->p_map[0][i + 5] = NULL;
		p->p_map[0][i + 6] = NULL;
		p->p_map[0][i + 7] = NULL;
		p->p_map[0][i + 8] = NULL;
		p->p_map[0][i + 9] = NULL;
		i += 10;
	}
}

void	init_struct_p(t_p *p)
{
	p->i_map = 0;
	p->fill = 0;
	p->shadow = 0;
	p->blur = 0;
	p->real_z = 1;
	p->pas = 1;
	p->fdf->rot_x = 90 / 180 *  PI;
	p->fdf->rot_y = 0 / 180 * PI;
	p->fdf->rot_z = 0 / PI;
	p->alt = 1;
	p->z = 15 / ACCURACY;
	p->win_x = 1300;
	p->win_y = 1000;
	p->color = 0x00FFFFFF;
	p->bcolor = 0x00FFFFFF;
	p->img_x = 1000;
	p->img_y = 1000;
	p->ui.img_x = 300;
	p->ui.img_y = 1000;
	p->act_p = NULL;
	make_p_map(p);
	clear_p_map(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, WINDOWS_NAME);
	p->image = mlx_new_image(p->mlx, p->img_x, p->img_y);
	p->addr = mlx_get_data_addr(p->image, &p->bpp, &p->line_size, &p->edian);
}

void	init_key_fonction(t_p *p)
{
	int		i;

	i = 0;
	while (i < 255)
	{
		init_key_fonction_a(p, i);
		i++;
	}
}

void	init_key_fonction_a(t_p *p, int i)
{
		if (i == 123)
			p->fct[i] = (void *)left;
		else if (i == 124)
			p->fct[i] = (void *)right;
		else if (i == 125)
			p->fct[i] = (void *)down;
		else if (i == 126)
			p->fct[i] = (void *)up;
		else if (i == 53)
			p->fct[i] = (void *)quit;
		else if (i == 37)
			p->fct[i] = (void *)draw_ptp;
		else if (i == 8)
			p->fct[i] = (void *)ft_clear_image;
//		else if (i == 12)
//			p->fct[i] = (void *)draw_things;
		else if (i == 69)
			p->fct[i] = (void *)zoom_in;
		else if (i == 78)
			p->fct[i] = (void *)zoom_out;
//		else if (i == 0)
//			p->fct[i] = (void *)a;
//		else if (i == 1)
//			p->fct[i] = (void *)s;
//		else if (i == 2)
//			p->fct[i] = (void *)d;
//		else if (i == 13)
//			p->fct[i] = (void *)w;
		else if (i == 85)
			p->fct[i] = (void *)trois;
		else if (i == 88)
			p->fct[i] = (void *)six;
		else
			p->fct[i] = NULL;
}
