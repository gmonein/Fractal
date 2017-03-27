/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_fonc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:05:43 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 03:24:22 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

	void  print_point(t_p *p)
	{
		int		x;
		int		y;

		y = -1;
		while (++y < p->fdf->h - 1 && (x = -1) != 0 && printf("\n"))
			while (++x < p->fdf->l)
				printf("%d,%d,%d ", p->fdf->map[y][x].x, p->fdf->map[y][x].y, p->fdf->map[y][x].z);
	}

void		draw_things(t_p *p)
{
	return ;
}

void		left(t_p *p)
{
	p->fdf->ofx -= 1 + P_PAS;
}

void		right(t_p *p)
{
	p->fdf->ofx += 1 + P_PAS;
}

void		up(t_p *p)
{
	p->fdf->ofy -= 1 + P_PAS;
}

void		down(t_p *p)
{
	p->fdf->ofy += 1 + P_PAS;
}

void		quit(t_p *p)
{
	exit(1);
}

void		zoom_in(t_p *p)
{
	p->z += 1;
}

void		zoom_out(t_p *p)
{
	p->z -= 1;
}

void		a(t_p *p)
{
	p->fdf->ofx--;
}

void		w(t_p *p)
{
	p->fdf->ofy--;
}

void		d(t_p *p)
{
	p->fdf->ofx++;
}

void		s(t_p *p)
{
	p->fdf->ofy++;
}

void		draw_ptp(t_p *p)
{
//	ft_draw_line(p, (t_coord){ p->p_zx, p->p_zy, p->p_x, p->p_y });
}

void		trois(t_p *p)
{
	p->alt -= 0.05;
}

void		six(t_p *p)
{
	p->alt += 0.05;
}

int		my_key_funct(int keycode, t_p *p)
{
	char	*str;
	void	(*fct)(t_ui_elem *, t_p *, int);

		//printf("keycode = %d\n", keycode);
		p->keycode = keycode;
		if (keycode == K_V)//89)
		{
			p->fdf->rot_x = 90;
			p->fdf->rot_y = 0;
			p->fdf->rot_z = 0;
			p->fdf->rot_x = (p->fdf->rot_x * PI) / 180;
			p->fdf->rot_y = (p->fdf->rot_y * PI) / 180;
			p->fdf->rot_z = (p->fdf->rot_z * PI) / 180;
		}
		else if (keycode == K_B)//89)
		{
			p->fdf->rot_x = 0;
			p->fdf->rot_y = 90;
			p->fdf->rot_z = 0;
			p->fdf->rot_x = (p->fdf->rot_x * PI) / 180;
			p->fdf->rot_y = (p->fdf->rot_y * PI) / 180;
			p->fdf->rot_z = (p->fdf->rot_z * PI) / 180;
		}
		else if (keycode == K_N)//89)
		{
			p->fdf->rot_x = 0;
			p->fdf->rot_y = 0;
			p->fdf->rot_z = 90;
			p->fdf->rot_x = (p->fdf->rot_x * PI) / 180;
			p->fdf->rot_y = (p->fdf->rot_y * PI) / 180;
			p->fdf->rot_z = (p->fdf->rot_z * PI) / 180;
		}
		else if (keycode == K_U && p->act_p != NULL)
			p->act_p->x += 1;
		else if (keycode == K_J && p->act_p != NULL)
			p->act_p->x -= 1;
		else if (keycode == K_I && p->act_p != NULL)
			p->act_p->y += 1;
		else if (keycode == K_K && p->act_p != NULL)
			p->act_p->y -= 1;
		else if (keycode == K_O && p->act_p != NULL)
			p->act_p->z += 1;
		else if (keycode == K_L && p->act_p != NULL)
			p->act_p->z -= 1;
		else if (keycode == K_R)
		{
			p->fdf->rot_x += RP;
			if (p->fdf->rot_x >= DPI)
				p->fdf->rot_x = 0;
		}
		else if (keycode == K_T)
		{
			p->fdf->rot_y += RP;
			if (p->fdf->rot_y >= DPI)
				p->fdf->rot_y = 0;
		}
		else if (keycode == K_Y)
		{
			p->fdf->rot_z += RP;
			if (p->fdf->rot_z >= DPI)
				p->fdf->rot_z = 0;
		}
		else if (keycode == K_F)
		{
			p->fdf->rot_x -= RP;
			if (p->fdf->rot_x < 0)
				p->fdf->rot_x = DPI;
		}
		else if (keycode == K_G)
		{
			p->fdf->rot_y -= RP;
			if (p->fdf->rot_y < 0)
				p->fdf->rot_y = DPI;
		}
		else if (keycode == K_H)
		{
			p->fdf->rot_z -= RP;
			if (p->fdf->rot_z < 0)
				p->fdf->rot_z = DPI;
		}
		else if (keycode == 122)//82)
		{
			if (p->fill >= 2)
				p->fill = 0;
			else
				p->fill++;
		}
		else if (keycode == 'u')
			p->i_map = (p->i_map < p->nb_map ? p->i_map + 1 : 0);
		else if (keycode == 'j')
			p->i_map = (p->i_map > 0 ? p->i_map - 1 : p->nb_map);
		else if (keycode == K_Z)
			p->z++;
		else if (keycode == K_X)
			p->z--;
		else if (keycode == K_D)
			p->fdf->ofx += 10;
		else if (keycode == K_A)
			p->fdf->ofx -= 10;
		else if (keycode == K_W)
			p->fdf->ofy -= 10;
		else if (keycode == K_S)
			p->fdf->ofy += 10;
		else if (keycode == K_C)
			print_point(p);
		else if (p->act_p != NULL)
		{
		 if (keycode == K_RIGHT && p->act_p->i_x < p->fdf->l - 3)
		    	p->act_p = &p->fdf->map[p->act_p->i_y][p->act_p->i_x + 1];
	   if (keycode == K_LEFT && p->act_p->i_x > 0)
		    	p->act_p = &p->fdf->map[p->act_p->i_y][p->act_p->i_x - 1];
     if (keycode == K_DOWN && p->act_p->i_y < p->fdf->h - 2)
		    	p->act_p = &p->fdf->map[p->act_p->i_y + 1][p->act_p->i_x];
     if (keycode == K_UP && p->act_p->i_y > 0)
		    	p->act_p = &p->fdf->map[p->act_p->i_y - 1][p->act_p->i_x];
		}
//		printf("%lf %lf %lf\n", p->fdf->rot_x, p->fdf->rot_y, p->fdf->rot_z);
//		if (p->fct[keycode] != NULL && keycode < 256 && keycode > -1)
//			(p->fct[keycode])(p);
		clear_p_map(p);
		ft_clear_image(p);
		ft_clear_zmap(p);
		fdf(p, -1, -1);
		mlx_put_image_to_window(p->mlx, p->win, p->image, 300, 0);
		//fdf_sphere(p, p->map[0])
		//  ftui_put_switch(p->test_s, &p->ui);
//		mlx_put_image_to_window(p->mlx, p->win, p->ui.image, 0, 0);
		if (p->act_clicked != NULL && p->act_clicked->fct[4] != NULL)
		{
			fct = p->act_clicked->fct[4];
			(fct)(p->act_clicked, p, keycode);
		}
	//	printf("button value = %d\n", p->fill);
		return (0);
}
