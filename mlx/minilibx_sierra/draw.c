/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:59:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 09:01:22 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			px2img(unsigned int color, int x, int y, double z, t_p *p)
{
	char	*rgb;
	int		i;
	int		j;
	char	blur;

	if (x + p->fdf->ofx > p->img_x - 1
			|| x + p->fdf->ofx < 0
			|| y + p->fdf->ofy > p->img_y - 1
			|| y + p->fdf->ofy < 0)
		return (-1);
	i = (int)(x + p->fdf->ofx) * (4) + ((int)(y + p->fdf->ofy) * p->line_size);
	j = (int)(x + p->fdf->ofx) + ((int)(y + p->fdf->ofy) * p->line_size);
	if (p->z_map[j].z == INT_MIN)
		p->z_map[j].z = z;
	if (p->z_map[j].z >= z)
	{
		blur = (p->blur == 1 ? z * 4 : 0xFF);
		rgb = (char*)&color;
		p->addr[i] = rgb[0] & blur;
		p->addr[i + 1] = rgb[1] & blur;
		p->addr[i + 2] = rgb[2] & blur;
		p->z_map[j].z = z;
	}
	return (1);
}

void		ft_clear_image(t_p *p)
{
	int		i;
	int		end;
	int 	color;
	int		*tab;

	tab = (int *)p->addr;
	i = 0;
	color = 0x00151515;
	end = p->img_x * p->img_y;
	while (i < end)
	{
		tab[i] = color;
		tab[i + 1] = color;
		tab[i + 2] = color;
		tab[i + 3] = color;
		tab[i + 4] = color;
		tab[i + 5] = color;
		tab[i + 6] = color;
		tab[i + 7] = color;
		tab[i + 8] = color;
		tab[i + 9] = color;
		i += 10;
	}
}

void		ft_clear_ui(t_p *p)
{
	int		i;
	int		end;
	int		color;
	int		*tab;

	tab = (int *)p->ui.addr;
	i = 0;
	color = UI_BG_COLOR;
	end = p->ui.img_x * p->ui.img_y;
	while (i < end)
	{
		tab[i] = color;
		tab[i + 1] = color;
		tab[i + 2] = color;
		tab[i + 3] = color;
		tab[i + 4] = color;
		tab[i + 5] = color;
		tab[i + 6] = color;
		tab[i + 7] = color;
		tab[i + 8] = color;
		tab[i + 9] = color;
		i += 10;
	}
}

void		ft_clear_zmap(t_p *p)
{
	int		i;
	int		end;

	i = 0;
	end = p->img_x * p->img_y * 4;
	while (i < end)
	{
		p->z_map[i].z = INT_MAX;
		p->z_map[i + 1].z = INT_MAX;
		p->z_map[i + 2].z = INT_MAX;
		p->z_map[i + 3].z = INT_MAX;
		p->z_map[i + 4].z = INT_MAX;
		p->z_map[i + 5].z = INT_MAX;
		p->z_map[i + 6].z = INT_MAX;
		p->z_map[i + 7].z = INT_MAX;
		p->z_map[i + 8].z = INT_MAX;
		p->z_map[i + 9].z = INT_MAX;
		i += 10;
	}
}

void		ft_draw_line(t_p *p, t_point a, t_point b)
{
	t_coord		c;

	c.dx = b.x - a.x;
	c.dy = b.y - a.y;
	c.steps = (abs(c.dx) > abs(c.dy) ? abs(c.dx) : abs(c.dy));
	c.x_inc = c.dx * (1.0 / c.steps);
	c.y_inc = c.dy * (1.0 / c.steps);
	c.x = a.x;
	c.y = a.y;
	c.i = 0;
	while (c.i <= c.steps)
	{
		px2img(p->color, c.x, c.y, INT_MAX, p);
		c.y += c.y_inc;
		c.x += c.x_inc;
		c.i++;
	}
}

t_coord		calc_line(t_p *p, t_point a, t_point b)
{
	t_coord		c;

	c.dx = b.x - a.x;
	c.dy = b.y - a.y;
	c.steps = (abs(c.dx) > abs(c.dy) ? abs(c.dx) : abs(c.dy));
	c.x_inc = c.dx * (1.0 / c.steps);
	c.y_inc = c.dy * (1.0 / c.steps);
	c.x = a.x;
	c.y = a.y;
	c.mid_x = c.x_inc * (c.steps * 0.5);
	c.i = 0;
	return (c);
}
