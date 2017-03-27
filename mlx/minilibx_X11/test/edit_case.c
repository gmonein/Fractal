/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:05:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/12 08:50:30 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void            ftui_edit_case_img_a(int x, int y, int *img)
{
    int     i;
    int     j;

    i = -1;
    while (++i < y && (j = -1) != 0)
        while (++j < x)
            if (i == 0 || j == 0 || j == x - 1 || i == y - 1)
                img[j + i * (x + 1)] = 0x00FFFFFF;
            else if (i == 1 || j == 1 || j == x - 2 || i == y - 2)
                img[j + i * x] = 0x00000000;
            else
                img[j + i * x] = 0xFF000000;
}

void            ftui_edit_case_img_b(int x, int y, int *img)
{
    int     i;
    int     j;

    i = -1;
    while (++i < y && (j = -1) != 0)
        while (++j < x)
            if (i == 0 || j == 0 || j == x - 1 || i == y - 1)
                img[j + i * (x + 1)] = 0x00FFFFFF;
            else if (i == 1 || j == 1 || j == x - 2 || i == y - 2)
                img[j + i * x] = 0x00A1A1A1;
            else
                img[j + i * x] = 0xFF000000;

}

void            ftui_edit_case_img_c(int x, int y, int *img)
{
    int     i;
    int     j;

    i = -1;
    while (++i < y && (j = -1) != 0)
        while (++j < x)
            if (i == 0 || j == 0 || j == x - 1 || i == y - 1)
                img[j + i * x] = 0x00FFFFFF;
            else if (i == 1 || j == 1 || j == x - 2 || i == y - 2)
                img[j + i * x] = 0x00CACACA;
            else
                img[j + i * x] = 0x00000000;
}

void            ftui_edit_case_img_d(int x, int y, int *img)
{
    int     i;
    int     j;

    i = -1;
    while (++i < y && (j = -1) != 0)
        while (++j < x)
            if (i == 0 || j == 0 || j == x - 1 || i == y - 1)
                img[j + i * x] = 0x00FFFFFF;
            else if (i == 1 || j == 1 || j == x - 2 || i == y - 2)
                img[j + i * x] = 0x00000000;
            else
                img[j + i * x] = 0x00000000;
}

void       ft_ui_edit_case_set_img(t_ui_elem *s, t_p *p)
{
    int     i;

   s->img = (void **)malloc(sizeof(void *) * 5);
   s->addr = (char **)malloc(sizeof(char *) * 5); 
   i = -1;
   while (++i != 4)
        s->img[i] = mlx_new_image(p->mlx, s->len_x, s->len_y);
   i = -1;
   while (++i != 4)
        s->addr[i] = mlx_get_data_addr(s->img[i], &s->bpp, &s->line_size, &s->edian);
    ftui_edit_case_img_a(s->len_x, s->len_y, (int *)s->addr[0]);
    ftui_edit_case_img_b(s->len_x, s->len_y, (int *)s->addr[1]);
    ftui_edit_case_img_c(s->len_x, s->len_y, (int *)s->addr[2]);
    ftui_edit_case_img_c(s->len_x, s->len_y, (int *)s->addr[3]);
}

t_ui_elem        *ftui_create_edit_case(t_ui_elem inf, t_p *p)
{
    t_ui_elem    *s;

    s = (t_ui_elem *)malloc(sizeof(t_ui_elem));
    s->name = ID_EDIT_CASE;
    s->pos_x = inf.pos_x;
    s->pos_y = inf.pos_y;
    s->len_x = inf.len_x;
    s->len_y = inf.len_y;
    s->elema = inf.elema;
    s->elemb = inf.elemb;
    ft_ui_edit_case_set_img(s, p);
    s->clicked = 0;
    s->fct[0] = (void *)ftui_edit_case_p_out;
    s->fct[1] = (void *)ftui_edit_case_p_in;
    s->fct[2] = (void *)ftui_edit_case_p_click_in;
    s->fct[3] = (void *)ftui_edit_case_p_click_out;
    s->fct[4] = (void *)ftui_edit_case_k;
    return (s);
}

void            ftui_put_edit_case(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    int i;
    int j;
    
    i = -1;
    while (++i < s->len_y && (j = -1) != 0)
        while (++j < s->len_x)
            ui->mask[i + s->pos_y][j + s->pos_x] = s;
}

void            ftui_edit_case_p_out(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    if (s->clicked == 0)
        mlx_put_image_to_window(p->mlx, p->win, s->img[0], s->pos_x, s->pos_y);
}

void            ftui_edit_case_p_in(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    if (s->clicked == 0)
        mlx_put_image_to_window(p->mlx, p->win, s->img[1], s->pos_x, s->pos_y);
}

void            ftui_edit_case_p_click_in(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    s->clicked = (s->clicked == 1 ? 0 : 1);
    if (s->clicked == 1)
        mlx_put_image_to_window(p->mlx, p->win, s->img[2], s->pos_x, s->pos_y);
}

void            ftui_edit_case_p_click_out(t_ui_elem *s, t_ui_image *ui, t_p *p)
{
    mlx_put_image_to_window(p->mlx, p->win, s->img[0], s->pos_x, s->pos_y);
    s->clicked = 0;
}

int             key_to_int(int k)
{
    if (k == K_ONE || k == K_NP_ONE)
        return (1);
    if (k == K_TWO || k == K_NP_TWO)
        return (2);
    if (k == K_THREE || k == K_NP_THREE)
        return (3);
    if (k == K_FOUR || k == K_NP_FOUR)
        return (4);
    if (k == K_FIVE || k == K_NP_FIVE)
        return (5);
    if (k == K_SIX || k == K_NP_SIX)
        return (6);
    if (k == K_SEVEN || k == K_NP_SEVEN)
        return (7);
    if (k == K_EIGHT || k == K_NP_EIGHT)
        return (8);
    if (k == K_NINE || k == K_NP_NINE)
        return (9);
    if (k == K_ZERO || k == K_NP_ZERO)
        return (0);
    return (-1);
}

void            ftui_edit_case_k(t_ui_elem *s, t_p *p, int keycode)
{
    char    *str;

    if (s->clicked == 1)
    {
        if (keycode == K_DELETE)
        {
            *(int *)s->elema /= 10;
        }
        else if ((keycode = key_to_int(keycode)) != -1)
        {
            *(int *)s->elema *= 10;
            *(int *)s->elema += keycode;
        }
        mlx_put_image_to_window(p->mlx, p->win, s->img[2], s->pos_x, s->pos_y);
        str = ft_itoa(*(int *)s->elema);
        mlx_string_put(p->mlx, p->win, s->pos_x + 4, s->pos_y + 2, 0xFFFFFF, str);
        free(str); 
    }
}