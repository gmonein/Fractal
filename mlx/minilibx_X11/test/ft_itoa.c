/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:05:43 by gmonein           #+#    #+#             */
/*   Updated: 2017/03/12 07:39:47 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_nbchar(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i++);
}

char			*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	num;

	num = n;
	len = ft_nbchar(n);
	if (!(str = (char *)malloc(sizeof(char) * (len) + 1)))
		return (NULL);
	str[len] = '\0';
	len--;
	if (num == 0)
		str[0] = '0';
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	if (num < 0)
		num *= -1;
	while (len >= 0)
	{
		str[len] = (num % 10) + '0';
		len--;
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}