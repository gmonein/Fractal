/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 23:24:24 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/18 08:08:03 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word_len(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list		*lst;
	t_list		*tmp;
	char		*tab;

	if (!s || (lst = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	tmp = lst;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		if (!(tab = (char *)malloc(sizeof(char) * ft_word_len(s, c))))
			return (NULL);
		tab = ft_strsub(s, 0, ft_word_len(s, c));
		s = s + ft_word_len(s, c);
		tmp->next = ft_lstnew(tab, sizeof(char *));
		tmp = tmp->next;
	}
	return (lst);
}
