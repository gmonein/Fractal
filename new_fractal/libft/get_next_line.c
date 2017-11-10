/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:26:16 by gmonein           #+#    #+#             */
/*   Updated: 2017/02/11 14:56:41 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	proceed(int const fd, char *buff, char **s)
{
	char	*p;
	char	*tmp;
	int		i;

	while ((p = ft_strchr(s[fd], '\n')) == NULL &&
		(i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		tmp = s[fd];
		if (!(s[fd] = ft_strjoin(tmp, buff)))
			return (-1);
		ft_strdel(&tmp);
	}
	ft_strdel(&buff);
	return (i == -1 ? -1 : 1);
}

int			get_next_line(int const fd, char **line)
{
	static char	*s[OPEN_MAX];
	char		*tmp;
	char		*str;
	char		*buff;

	if ((fd < 0 || !line || BUFF_SIZE < 1)
	|| ((buff = ft_strnew(BUFF_SIZE)) == NULL)
	|| (fd > (OPEN_MAX - 1))
	|| (!s[fd] && (s[fd] = ft_strnew(1)) == NULL)
	|| (proceed(fd, buff, s) == -1))
		return (-1);
	if ((str = ft_strchr(s[fd], '\n')) != NULL)
	{
		if (!(*line = ft_strsub(s[fd], 0, str - s[fd])))
			return (-1);
		tmp = s[fd];
		if (!(s[fd] = ft_strdup(str + 1)))
			return (-1);
		ft_strdel(&tmp);
		return (1);
	}
	if (!(*line = ft_strdup(s[fd])))
		return (-1);
	s[fd] = NULL;
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
