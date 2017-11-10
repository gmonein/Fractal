/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:17:04 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/04 18:20:40 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char		*ft_multijoin(char **to_join)
{
	int		i;
	size_t	len;
	char	*res;

	i = -1;
	if (!to_join)
		return (NULL);
	len = 0;
	while (to_join[++i])
		len += ft_strlen(to_join[i]);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	len = 0;
	while (to_join[++i])
	{
		ft_strcpy(res + len, to_join[i]);
		len += ft_strlen(to_join[i]);
	}
	res[len] = '\0';
	return (res);
}
