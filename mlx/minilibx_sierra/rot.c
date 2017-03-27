/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:26:58 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/02 11:12:46 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point		ft_rotate_x(t_point c, t_p *p)
{
	double	y;

	c.z -= p->fdf->dmid.z;
	c.y -= p->fdf->dmid.y;
	c.z *= 1000000;
	c.y *= 1000000;
	y = c.y;
	c.y = y * cos(p->fdf->rot_x) - c.z * sin(p->fdf->rot_x);
	c.z = y * sin(p->fdf->rot_x) + c.z * cos(p->fdf->rot_x);
	c.z /= 1000000;
	c.y /= 1000000;
	c.z += p->fdf->dmid.z;
	c.y += p->fdf->dmid.y;
	return (c);
}

static t_point		ft_rotate_z(t_point c, t_p *p)
{
	double	x;

	c.x -= p->fdf->dmid.x;
	c.y -= p->fdf->dmid.y;
	c.x *= 1000000;
	c.y *= 1000000;
	x = c.x;
	c.x = x * cos(p->fdf->rot_z) - c.y * sin(p->fdf->rot_z);
	c.y = x * sin(p->fdf->rot_z) + c.y * cos(p->fdf->rot_z);
	c.x /= 1000000;
	c.y /= 1000000;
	c.x += p->fdf->dmid.x;
	c.y += p->fdf->dmid.y;
	return (c);
}

static t_point		ft_rotate_y(t_point c, t_p *p)
{
	double	z;

	c.z -= p->fdf->dmid.z;
	c.x -= p->fdf->dmid.x;
	c.x *= 1000000;
	c.z *= 1000000;
	z = c.z;
	c.z = z * cos(p->fdf->rot_y) - c.x * sin(p->fdf->rot_y);
	c.x = z * sin(p->fdf->rot_y) + c.x * cos(p->fdf->rot_y);
	c.x /= 1000000;
	c.z /= 1000000;
	c.z += p->fdf->dmid.z;
	c.x += p->fdf->dmid.x;
	return (c);
}

t_point				ft_pos(t_i_point *a, t_point *b, t_p *p)
{
	t_point		c;

	if (a == NULL)
		c = (t_point){b->x, b->y, b->z};
	else if (b == NULL)
		c = (t_point){a->x, a->y, a->z};
	c = ft_rotate_x(c, p);
	c = ft_rotate_y(c, p);
	c = ft_rotate_z(c, p);
	c.z = c.y + c.x + c.z;
	c.x = p->z * c.x;
	c.y = p->z * c.y + c.z;
	return (c);
}
