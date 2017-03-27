/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:33:03 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/16 02:52:21 by jpeg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long int		ft_atoi(char *str)
{
	int		i;
	int		sign;
	int		result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] >= 0 && str[i] <= 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

unsigned		ft_conv_hex(char *str)
{
	unsigned	result;
	char		*s;

	s = &str[2];
	result = 0;
	while (*s)
	{
		result <<= 4;
		result |= (*s >= 'A' && *s <= 'F' ? 10 + *s - 'A' : *s - '0');
		s++;
	}
	return (result);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_isinhex(char s)
{
	if ((s >= '0' && s <= '9') || (s >= 'A' && s <= 'F'))
		return (1);
	return (0);
}

int		ft_ishex(char *s, int *j)
{
	if ((s[0] != '0' && (*j += 1) != -1)
		|| (s[1] != 'x' && (*j += 2) != -1)
		|| (ft_isinhex(s[2]) == 0 && (*j += 3) != -1)
		|| (ft_isinhex(s[3]) == 0 && (*j += 4) != -1)
		|| (ft_isinhex(s[4]) == 0 && (*j += 5) != -1)
		|| (ft_isinhex(s[5]) == 0 && (*j += 6) != -1)
		|| (ft_isinhex(s[6]) == 0 && (*j += 7) != -1)
		|| (ft_isinhex(s[7]) == 0 && (*j += 8) != -1)
		|| (ft_isinhex(s[8]) == 1 && (*j += 9) != -1))
		return (0);
	*j += 9;
	return (1);
}

int			pars_error(int line, int col, int c, char *error)
{
	if (line != -1)
	{
		line += 1;
		col += 1;
		ft_putstr_fd("(line: ", 2);
		ft_putnbr_fd(line, 2);
		if (col != -1)
		{
			ft_putstr_fd(", col: ", 2);
			ft_putnbr_fd(col, 2);
		}
		if (c != (int)NULL)
		{
			ft_putstr_fd(", char : ", 2);
			ft_putchar_fd('\'', 2);
			ft_putchar_fd(c, 2);
			ft_putchar_fd('\'', 2);
		}
		ft_putstr_fd("): ", 2);
	}
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int			ft_isdigit_sign(char *c)
{
	int		i;

	i = 0;
	if (c[i] == '+' || c[i] == '-')
		i++;
	if (c[i] >= '0' && c[i] <= '9')
		return (2);
	return (0 + i);
}

int		ft_count_number(char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 1;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		n++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (n);
}

int			ft_count_line(int fd, char **line)
{
	int		i;
	int		j;
	char	*str;
	int		error;
	int		tmp;

	i = 0;
	error = 0;
	tmp = 0;
	while (get_next_line(fd, line) > 0)
	{
		j = 0;
		if (!**line)
			error = pars_error(i, -1, (int)NULL, E_EMPTY_LINE);
		str = *line;
		while (str[j])
		{
			if ((tmp = ft_isdigit_sign(&str[j])) != 2)
			{
				j += tmp;
				error = pars_error(i, j, str[j], E_INVALID_CHAR);
			}
			while (++j && str[j] != '\n' && str[j] != ',' && str[j] != '-'
					&& str[j] != '\0' && str[j] != ' ' && str[j] != '+')
				if (str[j] < '0' || str[j] > '9')
					error = pars_error(i, j, str[j], E_INVALID_CHAR);
			if (str[j] == '\n' || str[j] == '\0')
			{
				if (str[j] == '\n' && str[j + 1] == '\0')
					return (pars_error(i, j, (int)NULL, E_SPACE_END));
				else
					break;
			}
			if (str[j] == ',' && ft_ishex(&str[j + 1], &j) == 0)
				error = pars_error(i, j, (int)NULL, E_HEXA_FORMAT);
			if (str[j] != ' ' && str[j] != '\0' && str[j] != '\n')
			{
				error = pars_error(i, j, str[j], E_INVALID_CHAR);
				j++;
			}
			while (str[j] == ' ')
				j++;
		}
		i++;
		free(*line);
	}
	return ((error == -1 ? -1 : i));
}

t_i_point		*pars_dot_line(char *str, int *l, int *m_z, int y)
{
	t_i_point *dot;
	int		i;
	int		j;

	*l = (*l <= -1 ? ft_count_number(str) : *l);
	if (*l <= -1)
		return NULL;
	dot = (t_i_point *)malloc(sizeof(t_i_point) * *l);
	i = 0;
	j = 0;
	while (str[i])
	{
		dot[j] = (t_i_point){j, y, ft_atoi(&str[i]), j, y};
		*m_z += dot[j].z;
		while (str[i] != ' ' && str[i])
		{
			i++;
			dot[j].c[0] = (str[i] == ',' ? 1 : 0);
			dot[j].c[1] = (str[i] == ',' ? ft_conv_hex(&str[i + 1]) : 0);
		}
		while (str[i] && str[i] == ' ')
			i++;
		j++;
	}
	free(str);
	return (dot);
}

t_i_point		**pars_point(char *file, int *l, int *h, int *m_z)
{
	t_i_point	**dot;
	char		*line;
	int			fd;
	int			i;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Unable to read : ", 2);
		ft_putstr_fd(file, 2);
		return (NULL);
	}
	*h = ft_count_line(fd, &line);
	if (*h == -1)
		return (NULL);
	close(fd);
	fd = open(file, O_RDONLY);
	dot = (t_i_point **)malloc(sizeof(t_i_point *) * *h);
	i = -1;
	*l = -1;
	*m_z = 0;
	while (++i != -1 && get_next_line(fd, &line) > 0)
		dot[i] = pars_dot_line(line, l, m_z, i);
	*m_z /= (*l * *h);
	return (dot);
}
