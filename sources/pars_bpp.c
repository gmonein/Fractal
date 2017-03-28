/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bpp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:05:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/28 11:21:18 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		ft_bpp_get_size(int fd, t_ui_elem *s)
{
	char	*line;
	int		i;

	get_next_line(fd, &line);
	while (!(line[0] >= '0' && line[0] <= '9'))
	{
		free(line);
		get_next_line(fd, &line);
	}
	s->len_x = ft_atoi(line);
	i = 0;
	while (line[i] != ' ')
		i++;
	s->len_y = ft_atoi(&line[i + 1]);
	free(line);
	get_next_line(fd, &line);
	free(line);
	get_next_line(fd, &line);
	free(line);
}

static void		ft_malloc_bpp(t_p *p, t_ui_elem *s, int i, int fd)
{
	char	*line;
	int		j;
	int		len_x;
	char	val;

	ft_bpp_get_size(fd, s);
	s->img[i] = mlx_new_image(p->mlx, s->len_x, s->len_y);
	s->addr[i] = mlx_get_data_addr(s->img[i], &s->bpp, \
			&s->line_size, &s->edian);
	j = 0;
	while (++j != -1 && get_next_line(fd, &line) > 0)
	{
		if (j % 4 == 3)
		{
			s->addr[i][j] = 0x0;
			j++;
		}
		val = ft_atoi(line);
		s->addr[i][j] = (val == 0 ? 0x20 : val);
		free(line);
	}
	free(line);
}

void			ft_ui_pars_switch_2(char *path, t_ui_elem *s, t_p *p)
{
	int		fd;
	char	*apath;
	char	*line;

	apath = ft_strjoin(path, "3.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 3, fd);
	close(fd);
}

void			ft_ui_pars_switch(char *path, t_ui_elem *s, t_p *p)
{
	int		fd;
	char	*apath;
	char	*line;

	s->addr = (char **)malloc(sizeof(char *) * 5);
	s->img = (void **)malloc(sizeof(void *) * 5);
	apath = ft_strjoin(path, "0.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 0, fd);
	close(fd);
	apath = ft_strjoin(path, "1.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 1, fd);
	close(fd);
	apath = ft_strjoin(path, "2.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 2, fd);
	close(fd);
	ft_ui_pars_switch_2(path, s, p);
	s->img[4] = NULL;
	s->addr[4] = NULL;
}

void			ft_ui_pars_button(char *path, t_ui_elem *s, t_p *p)
{
	int		fd;
	char	*apath;

	s->addr = (char **)malloc(sizeof(char *) * 4);
	s->img = (void **)malloc(sizeof(void *) * 4);
	apath = ft_strjoin(path, "0.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 0, fd);
	close(fd);
	apath = ft_strjoin(path, "1.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 1, fd);
	close(fd);
	apath = ft_strjoin(path, "2.ppm");
	fd = open(apath, O_RDONLY);
	free(apath);
	ft_malloc_bpp(p, s, 2, fd);
	close(fd);
	s->img[3] = NULL;
	s->addr[3] = NULL;
}
