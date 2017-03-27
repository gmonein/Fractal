/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 13:45:11 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 09:01:42 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int							normal_color(t_point a, t_point b, t_point c, int col)
{
		double		d_x;
		double		d_y;
		double		d_z;
		int				color;
		char			v;

		d_x = (b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y);
		d_y = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z);
		d_z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		color = 0;
		v = d_z + d_x + d_y;
		v /= 2;
		v += 127;
		color = v + (v << 8) + (v << 16) + 0xFF000000;
		return (col & color);
}

static void		fill_plan(t_p *p, t_point a, t_point b, t_point c)
{
	t_fill_plan		s;

	s = (t_fill_plan){ft_min(a.x, b.x, c.x), ft_max(a.x, b.x, c.x), \
		ft_min(a.y, b.y, c.y), ft_max(a.y, b.y, c.y)};
	s.y = s.miny;
	s.x = s.minx;
	while (s.y < s.maxy)
	{
		s.y++;
		s.x = s.minx;
		while (s.x < s.maxx)
		{
			s.x++;
			if (((a.x - b.x) * (s.y - a.y) - (a.y - b.y) * (s.x - a.x) > 0 &&
			(b.x - c.x) * (s.y - b.y) - (b.y - c.y) * (s.x - b.x) > 0 &&
			(c.x - a.x) * (s.y - c.y) - (c.y - a.y) * (s.x - c.x) > 0)
			|| ((a.x - b.x) * (s.y - a.y) - (a.y - b.y) * (s.x - a.x) < 0 &&
			(b.x - c.x) * (s.y - b.y) - (b.y - c.y) * (s.x - b.x) < 0 &&
			(c.x - a.x) * (s.y - c.y) - (c.y - a.y) * (s.x - c.x) < 0))
				px2img(p->color, s.x, s.y, a.z, p);
		}
	}
}
/*
static void		draw_axes_map(t_p *p)
{
	t_point		a;
	t_point		b;

	a = ft_pos((t_i_point){ p->xz + 400, p->yz, p->zz}, p);
	b = ft_pos((t_point){ p->xz - 400, p->yz, p->zz}, p);
	p->color = 0x00FF0000;
	ft_draw_line(p, a, b);
	a = ft_pos((t_point){ p->xz, p->yz + 400, p->zz}, p);
	b = ft_pos((t_point){ p->xz, p->yz - 400, p->zz}, p);
	p->color = 0x0000FF00;
	ft_draw_line(p, a, b);
	a = ft_pos((t_point){ p->xz, p->yz, p->zz + 400}, p);
	b = ft_pos((t_point){ p->xz, p->yz, p->zz - 400}, p);
	p->color = 0x000000FF;
	ft_draw_line(p, a, b);
}*/

static unsigned		color_by_alt(t_p *p, t_i_point a)
{
	if (a.c[0] == 0)
	{
		if (a.z <= 0 && p->colorize == 1)
			return (0x000000FF);
		if (a.z <= 20 && p->colorize == 1)
			return (0x0000FF00);
		return (0x00A1A1A1);
	}
	else
		return (a.c[1]);
	return (0x00FFFFFF);
}

static void			ft_fill(t_sqrt s, t_p *p)
{
	if (p->fill == 1)
	{
		if (p->colorize == 0)
			p->color = 0x00FFFFFF;
		if (p->shadow == 1)
			p->color = normal_color(s.a, s.b, s.c, p->color);
		fill_plan(p, s.c, s.b, s.a);
		if (p->colorize == 0)
			p->color = 0x00A1A1A1;
		if (p->shadow == 1)
			p->color = normal_color(s.a, s.b, s.c, p->color);
		fill_plan(p, s.c, s.b, s.d);
	}
}

void				set_to_p_map(t_p *p, t_i_point *a, t_point b)
{
	int			x;
	int			y;
	int		*tab;
	int		i_x;
	int		i_y;

	tab = (int *)p->addr;
	y = -5;
	while (++y < 5 && (x = -5) != 0)
		while (++x < 5)
		{
			i_x = (int)b.x + p->fdf->ofx + x;
			i_y = (int)b.y + y + p->fdf->ofy;
			if (i_x >= 0 && i_x < p->img_x && i_y < p->img_y && i_y >= 0)
			{
				p->p_map[i_y][i_x] = a;
				if (a == p->act_p)
						tab[(i_y) * p->img_x + i_x]= 0xA100FF00;
			}
		}
}

void				fdf(t_p *p, int i, int j)
{
	t_sqrt		s;
	t_sqrt    rs;

	while (++i < p->fdf->h - 1 && (j = -1) != 0)
		while (++j < p->fdf->l - 2 && (p->color = color_by_alt(p, p->fdf->map[i][j])))
		{
			s.a = ft_pos(&p->fdf->map[i][j], NULL, p);
			if (i - 1 > -1)
			{
				s.b = ft_pos(&p->fdf->map[i - 1][j], NULL, p);
				ft_draw_line(p, s.a, s.b);
			}
			if (j - 1 > -1)
			{
				s.c = ft_pos(&p->fdf->map[i][j - 1], NULL, p);
				ft_draw_line(p, s.a, s.c);
			}
			if (j - 1 > -1 && i - 1 > -1)
			{
				s.d = ft_pos(&p->fdf->map[i - 1][j - 1], NULL, p);
					ft_fill(s, p);
			}
			set_to_p_map(p, &p->fdf->map[i][j], s.a);
		}
}

static t_point		sphere(double v, double u, double r)
{
	t_point		p;

	p.x = r * cos(PI * u / 180.0) * cos(PI * v / 180);
	p.y = r * cos(PI * v / 180.0) * sin(PI * u / 180);
	p.z = r * sin(PI * v / 180);
	return (p);
}

/*
void		fdf_sphere(t_p *p, t_pars map)
{
	short		u;
	short		v;
	int			h;
	int			l;
	double		u_inc;
	double		v_inc;
	int			y;
	int			x;
	t_point		a;
	t_point		b;
	t_point		c;
	t_point		d;
	t_point		bak_a;
	int			a_set;

	h = 0;
	while (map.i[h])
		h++;
	l = map.len[1];
	u_inc = 360 / (h - 2);
	v_inc = 360 / (l - 1);
	x = 0;
	y = 0;
	u = 0;
	while ((int)u < 360)
	{
		x = 0;
		v = 0;
		a_set = 0;
		while ((int)v < 360)
		{
			a = sphere(u, v, 2 + map.i[y][x].z * p->alt);
			a = ft_pos(a, p);
			if (y - 1 > 0 && a_set == 0)
			{
				a_set = 1;
				bak_a = a;
			}
			if (y - 1 >= 0)
			{
				b = sphere(u - u_inc, v, 2 + map.i[y - 1][x].z * p->alt);
				b = ft_pos(b, p);
				ft_draw_line(p, a, b);
			}
			if (x - 1 >= 0)
			{
				c = sphere(u, v - v_inc, 2 + map.i[y][x - 1].z * p->alt);
				c = ft_pos(c, p);
				ft_draw_line(p, a, c);
			}
			if (x - 1 > -1 && y - 1 > -1)
			{
				d = sphere(u - u_inc, v - v_inc, map.i[x - 1][y - 1].z * p->alt);
				d = ft_pos(d, p);
				ft_fill((t_sqrt){a, b, c, d}, p);
			}
			v += v_inc;
			x++;
		}
		if (a_set == 1)
			ft_draw_line(p, a, bak_a);
		u += u_inc;
		y++;
	}
}
*/
