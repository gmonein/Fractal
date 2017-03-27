/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:09:29 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 05:19:44 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
int	mouse_btclic(int button, int x, int y, t_p *p)
{
	//t_switch *s;
	void	(*fct)(t_ui_elem *, t_ui_image *, t_p *);

	if (x >= 0 && x < 300 && y >= 0 && y < 1000)
	{
		if (p->ui.mask[y][x] != p->act_clicked && p->act_clicked != NULL && p->act_clicked->fct[3] != NULL)
		{
			fct = p->act_clicked->fct[3];
			(fct)(p->act_clicked, &p->ui, p);
			p->act_clicked = NULL;
		}
		if (p->ui.mask[y][x] != NULL)
		{
			p->act = p->ui.mask[y][x];
			if (p->act != NULL && p->act->fct[2] != NULL)
			{
				p->act_clicked = p->act;
				fct = p->act->fct[2];
				(fct)(p->ui.mask[y][x], &p->ui, p);
				clear_p_map(p);
				ft_clear_image(p);
				ft_clear_zmap(p);
				fdf(p, -1, -1);
				mlx_put_image_to_window(p->mlx, p->win, p->image, 300, 0);
			}
		}
	}
	t_i_point		*a;
	if (x >= 300 && x < 1300 && y >= 0 && y < 1000)
	{
		if (p->p_map[y] && p->p_map[y][x - 300] != NULL)
		{
			p->act_p = p->p_map[y][x - 300];
//			a = p->p_map[y][x - 300];
//			a->z += 1;
			clear_p_map(p);
			ft_clear_zmap(p);
			ft_clear_image(p);
			fdf(p, -1, -1);
			mlx_put_image_to_window(p->mlx, p->win, p->image, 300, 0);
		}
	}
	return (0);
}
int	mouse_bta(int x, int y, t_p *p)
{
	//t_switch *s;
	void	(*fct)(t_ui_elem *, t_ui_image *, t_p *);

	if (x >= 0 && x < 300 && y >= 0 && y < 1000)
	{
		if (p->ui.mask[y][x] != p->act)
		{
			if (p->act != NULL && p->act->fct[0] != NULL)
			{
				fct = p->act->fct[0];
				(fct)(p->act, &p->ui, p);
			}
			p->act = p->ui.mask[y][x];
			if (p->act != NULL && p->act->fct[1] != NULL)
			{
				fct = p->act->fct[1];
				(fct)(p->ui.mask[y][x], &p->ui, p);
			}
		}
	}
	return (0);
}

void	action(int *fill)
{
	*fill = (*fill == 0 ? 2 : 0);
	printf("%d\n", *fill);
	return ;
}

t_i_point		**make_point_map(int x, int y)
{
	int		i;
	int		j;
	t_i_point	**map;
	int		len;

	map = (t_i_point **)malloc(sizeof(t_i_point *) * y);
	map[0] = (t_i_point *)malloc(sizeof(t_i_point) * y * x);
	i = -1;
	len = x * y;
	while (++i < len)
	{
		if (i % x == 0)
			map[i / x] = &map[0][i];
		map[0][i] = (t_i_point){i % y, i / y, 0, i % y, i / y};
	}
	return(map);
}

int		main(int argc, char **argv)
{
	t_p		p;
	int		i;
	t_point	tmp;

	p.act = NULL;
	if (argc != 1)
	{
		i = 0;
		p.name = &argv[1];
		p.i_map = 0;
		p.fdf_tab = (t_image *)malloc(sizeof(t_image) * argc);
		if (argv[1][0] == '-')
		{
			int x;
			int y;

			x = ft_atoi(argv[2]) + 1;
			y = ft_atoi(argv[3]) + 1;
			p.fdf_tab[0].h = y;
			p.fdf_tab[0].l = x;
			p.fdf_tab[0].map = make_point_map(x, y);
			p.fdf_tab[0].mid = (t_i_point){x >> 1, y >> 1, 0};
			p.fdf_tab[0].dmid = (t_point){x / 2, y / 2, 0};
			i = 2;
		}
		else
			while (++i < argc)
			{
				p.fdf_tab[i - 1].map = pars_point(argv[i], &p.fdf_tab[i - 1].l, &p.fdf_tab[i - 1].h, &p.fdf_tab[i - 1].mid.z);
				p.fdf_tab[i - 1].mid = (t_i_point){p.fdf_tab[i - 1].l >> 1, p.fdf_tab[i - 1].h >> 1, p.fdf_tab[i - 1].mid.z};
				p.fdf_tab[i - 1].dmid = (t_point){p.fdf_tab[i - 1].mid.x, p.fdf_tab[i - 1].mid.y, p.fdf_tab[i - 1].mid.z};
			}
		p.fdf = &p.fdf_tab[0];
		p.nb_map = i - 2;
		init_struct_p(&p);
		init_key_fonction(&p);
		p.z_map = (t_zmap *)malloc(sizeof(t_zmap) * p.win_x * p.win_y * 4);
		fdf(&p, -1, -1);
	}
	mlx_hook(p.win, 2, (1L<<0), my_key_funct, &p);
	mlx_hook(p.win, 6, (1L<<6), mouse_bta, &p);
	mlx_mouse_hook(p.win, mouse_btclic, &p);
//	mlx_do_key_autorepeaton(p.mlx);
	mlx_put_image_to_window(p.mlx, p.win, p.image, 0, 0);
	make_ui(&p);
	mlx_loop(p.mlx);
}
