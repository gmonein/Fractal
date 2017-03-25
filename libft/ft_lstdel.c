/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 01:57:31 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/15 02:06:40 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*list;
	t_list		*lnext;

	list = *alst;
	while (list)
	{
		lnext = list->next;
		del(list->content, list->content_size);
		free(list);
		list = lnext;
	}
	*alst = NULL;
}
