/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 23:24:24 by gmonein           #+#    #+#             */
/*   Updated: 2016/11/15 01:07:47 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_word(char const *s, char c)
{
	int		word;
	int		is_word;

	word = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && is_word == 0)
		{
			is_word = 1;
			word++;
		}
		if (*s == c)
			is_word = 0;
		s++;
	}
	return (word);
}

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

char			**ft_strsplit(char const *s, char c)
{
	int		j;
	int		word_num;
	char	**split;

	j = 0;
	if (!s)
		return (NULL);
	word_num = ft_count_word(s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (word_num + 1))))
		return (NULL);
	while (word_num--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (!(split[j] = (char *)malloc(sizeof(char) * ft_word_len(s, c))))
			return (NULL);
		split[j] = ft_strsub(s, 0, ft_word_len(s, c));
		s = s + ft_word_len(s, c);
		j++;
	}
	split[j] = NULL;
	return (split);
}
