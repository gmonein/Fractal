/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:24:15 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/04 23:10:04 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_strndup(char *str, size_t len)
{
	char	*res;
	size_t	real_len;

	if (!str || !len)
		return (NULL);
	real_len = ft_strlen(str);
	real_len = (real_len > len ? len : real_len);
	res = (char *)malloc(sizeof(char) * (real_len + 1));
	ft_memcpy(res, str, sizeof(char) * real_len);
	res[real_len] = '\0';
	return (res);
}
