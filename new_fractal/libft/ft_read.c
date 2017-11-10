/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 00:28:22 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/20 09:37:40 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(char *file)
{
	int		fd;
	size_t	readed;
	char	*tab;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	fd = open(file, O_RDONLY);
	readed = read(fd, buf, BUF_SIZE);
	buf[readed] = '\0';
	tab = ft_strnew(readed + 1);
	while (readed == BUF_SIZE)
	{
		tab = ft_strjoin(tab, buf);
		readed = read(fd, buf, BUF_SIZE);
		buf[readed] = '\0';
		if (readed != BUF_SIZE)
			tab = ft_strjoin(tab, buf);
	}
	close(fd);
	free(buf);
	return (tab);
}
