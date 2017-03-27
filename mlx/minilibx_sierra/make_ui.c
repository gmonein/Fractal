/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:33:03 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 04:47:15 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void                left_click(t_p *p)
{
    int     len;
    char    *str;

    p->i_map = (p->i_map == 0 ? p->nb_map : p->i_map - 1);
    p->fdf = &p->fdf_tab[p->i_map];
    str = ft_strrchr(p->name[p->i_map], '/');
    mlx_put_image_to_window(p->mlx, p->win, p->ui_elems.image, 36, 20);
    len = ft_strlen((str == NULL ? p->name[p->i_map] : str + 1));
    len *= 5;
    p->act_p = NULL;
    mlx_string_put(p->mlx, p->win, 150 - len, 18, 0xFFFFFF, (str == NULL ? p->name[p->i_map] : str + 1));
}

void                right_click(t_p *p)
{
    int     len;
    char    *str;

    p->i_map = (p->i_map == p->nb_map ? 0 : p->i_map + 1);
    p->fdf = &p->fdf_tab[p->i_map];
    str = ft_strrchr(p->name[p->i_map], '/');
    mlx_put_image_to_window(p->mlx, p->win, p->ui_elems.image, 36, 20);
    len = ft_strlen((str == NULL ? p->name[p->i_map] : str + 1));
    len *= 5;
    p->act_p = NULL;
    mlx_string_put(p->mlx, p->win, 150 - len, 18, 0xFFFFFF, (str == NULL ? p->name[p->i_map] : str + 1));
}

static void        ui_change_map(t_p *p)
{
        int     len;
        int     i;
        char    *str;

        i = -1;
        p->ui_elems.image = mlx_new_image(p->mlx, 228, 20);
        p->ui_elems.addr = (int *)mlx_get_data_addr(p->ui_elems.image, &p->ui_elems.bpp, &p->ui_elems.line_size, &p->ui_elems.edian);
        while (++i < 4560)
            p->ui_elems.addr[i] = UI_BG_COLOR;
		p->ui_elems.b_l_select = ftui_create_button((t_ui_elem){0, 20, 20, 16, 16, (void *)left_click, p}, "ressource/ftui/lbutton/", p);
        ftui_put_elem(p->ui_elems.b_l_select, &p->ui, p);
		p->ui_elems.b_r_select = ftui_create_button((t_ui_elem){0, 264, 20, 16, 16, (void *)right_click, p}, "ressource/ftui/rbutton/", p);
        ftui_put_elem(p->ui_elems.b_r_select, &p->ui, p);
        str = ft_strrchr(p->name[p->i_map], '/');
        len = ft_strlen((str == NULL ? p->name[p->i_map] : str + 1));
        len *= 5;
        mlx_string_put(p->mlx, p->win, 150 - len, 18, 0xFFFFFF, (str == NULL ? p->name[p->i_map] : str + 1));
}

static void        ui_background(t_p *p)
{
   		p->act = NULL;
		p->act_clicked = NULL;
		p->ui.image = mlx_new_image(p->mlx, p->ui.img_x, p->ui.img_y);
		p->ui.addr = mlx_get_data_addr(p->ui.image, &p->ui.bpp, &p->ui.line_size, &p->ui.edian);
		p->ui.mask = ftui_malloc_mask(p->ui.img_x, p->ui.img_y);
		ftui_clear_mask(p->ui.img_x, p->ui.img_y, p->ui.mask);
		ft_clear_ui(p);
		mlx_put_image_to_window(p->mlx, p->win, p->ui.image, 0, 0);
}

static void        ui_fill_switch(t_p *p)
{
	 	p->ui_elems.s_fill = ftui_create_switch((t_ui_elem){0, 20, 50, 16, 16, &p->fill}, "ressource/ftui/switch/", p);
		ftui_put_elem(p->ui_elems.s_fill, &p->ui, p);
        mlx_string_put(p->mlx, p->win, 39, 48, 0xFFFFFF, "Fill");
	 	p->ui_elems.s_color = ftui_create_switch((t_ui_elem){0, 20, 70, 16, 16, &p->colorize}, "ressource/ftui/switch/", p);
		ftui_put_elem(p->ui_elems.s_color, &p->ui, p);
        mlx_string_put(p->mlx, p->win, 39, 68, 0xFFFFFF, "Colorize");
	 	p->ui_elems.s_shadow = ftui_create_switch((t_ui_elem){0, 20, 90, 16, 16, &p->shadow}, "ressource/ftui/switch/", p);
		ftui_put_elem(p->ui_elems.s_shadow, &p->ui, p);
        mlx_string_put(p->mlx, p->win, 39, 88, 0xFFFFFF, "Shadow");
	 	p->ui_elems.s_shadow = ftui_create_switch((t_ui_elem){0, 20, 110, 16, 16, &p->blur}, "ressource/ftui/switch/", p);
		ftui_put_elem(p->ui_elems.s_shadow, &p->ui, p);
        mlx_string_put(p->mlx, p->win, 39, 108, 0xFFFFFF, "Blur");
	 	p->ui_elems.s_shadow = ftui_create_switch((t_ui_elem){0, 20, 130, 16, 16, &p->blur}, "ressource/ftui/switch/", p);
		ftui_put_elem(p->ui_elems.s_shadow, &p->ui, p);
        mlx_string_put(p->mlx, p->win, 39, 128, 0xFFFFFF, "Simplify deep");
}

void        make_ui(t_p *p)
{
        ui_background(p);
        ui_change_map(p);
        ui_fill_switch(p);
}
