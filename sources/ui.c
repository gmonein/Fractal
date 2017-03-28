/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:05:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/23 16:52:30 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ftui_put_elem(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
	int		x;
	int		y;

	y = -1;
	while (++y <= s->len_y && (x = -1) != -2)
		while (++x < s->len_x)
			ui->mask[y + s->pos_y][x + s->pos_x] = s;
	mlx_put_image_to_window(p->mlx, p->win, s->img[0], s->pos_x, s->pos_y);
}

void		***ftui_malloc_mask(int x, int y)
{
	int		i;
	void	***mask;

	i = -1;
	mask = (void ***)malloc(sizeof(void **) * (y + 1));
	mask[y] = NULL;
	while (++i < y)
	{
		mask[i] = (void **)malloc(sizeof(void *) * (x + 1));
		mask[i][x] = NULL;
	}
	return (mask);
}

void		ftui_clear_mask(int x, int y, void ***mask)
{
	int		i;
	int		j;

	i = -1;
	while (++i < y - 1 && (j = -1) != 0)
		while (++j < x - 1)
			mask[i][j] = NULL;
}
