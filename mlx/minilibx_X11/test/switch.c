/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:05:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/12 07:55:01 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void            ftui_switch_p_out(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    mlx_put_image_to_window(p->mlx, p->win, s->img[0 + (*(int *)s->elema != 0 ? 1 : 0)], s->pos_x, s->pos_y);
}

void            ftui_switch_p_in(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    mlx_put_image_to_window(p->mlx, p->win, s->img[2 + (*(int *)s->elema != 0 ? 1 : 0)], s->pos_x, s->pos_y);
}

void            ftui_switch_p_click(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    printf("1\n");
    *(int *)s->elema = (*(int *)s->elema > 0 ? 0 : 1);
    printf("1\n");
    mlx_put_image_to_window(p->mlx, p->win, s->img[2 + (*(int *)s->elema != 0 ? 1 : 0)], s->pos_x, s->pos_y);
}

t_ui_elem        *ftui_create_switch(t_ui_elem inf, char *path, t_p *p)
{
    t_ui_elem    *s;

    s = (t_ui_elem *)malloc(sizeof(t_ui_elem));
    s->name = 1;
    s->pos_x = inf.pos_x;
    s->pos_y = inf.pos_y;
    s->len_x = inf.len_x;
    s->len_y = inf.len_y;
    s->elema = inf.elema;
    ft_ui_pars_switch(path, s, p);
    s->fct[0] = (void *)ftui_switch_p_out;
    s->fct[1] = (void *)ftui_switch_p_in;
    s->fct[2] = (void *)ftui_switch_p_click;
    s->fct[3] = NULL;
    s->fct[4] = NULL;
    *(int *)s->elema = (*(int *)s->elema != 0 && *(int *)s->elema != 1 ? 0 : *(int *)s->elema);
    return (s);
}