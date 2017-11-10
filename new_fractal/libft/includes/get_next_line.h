/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 06:11:47 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/05 18:14:47 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 1
# endif
# define BUFF_SIZE 3

int				get_next_line(int const fd, char **line);

#endif
