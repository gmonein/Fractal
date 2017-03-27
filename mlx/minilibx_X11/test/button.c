/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:05:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/12 07:54:45 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"




void            ftui_button_p_out(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    mlx_put_image_to_window(p->mlx, p->win, s->img[0], s->pos_x, s->pos_y);
}

void            ftui_button_p_in(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    mlx_put_image_to_window(p->mlx, p->win, s->img[1], s->pos_x, s->pos_y);
}

void            ftui_button_p_click(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    int     *img;
    int     i;
    int     j;
	void	(*fct)(void *);
    
    fct = s->elema;
    (fct)(s->elemb);
    mlx_put_image_to_window(p->mlx, p->win, s->img[2], s->pos_x, s->pos_y);
}

t_ui_elem        *ftui_create_button(t_ui_elem inf, char *path, t_p *p)
{
    t_ui_elem    *s;

    s = (t_ui_elem *)malloc(sizeof(t_ui_elem));
    s->name = inf.name;
    s->pos_x = inf.pos_x;
    s->pos_y = inf.pos_y;
    s->len_x = inf.len_x;
    s->len_y = inf.len_y;
    s->elema = inf.elema;
    s->elemb = inf.elemb;
    ft_ui_pars_button(path, s, p);
    s->fct[0] = (void *)ftui_button_p_out;
    s->fct[1] = (void *)ftui_button_p_in;
    s->fct[2] = (void *)ftui_button_p_click;
    s->fct[3] = NULL;
    s->fct[4] = NULL;
    return (s);
}