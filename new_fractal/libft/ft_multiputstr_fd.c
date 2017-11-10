/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiputstr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:53:50 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/04 18:54:30 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void		ft_multiputstr_fd(char **str, int fd)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putstr_fd(*str, fd);
		str++;
	}
}
