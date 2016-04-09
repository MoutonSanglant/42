/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 03:10:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**set(char **table, int idx, char *str)
{
	int i;

	i = 0;
	table[idx] = str;
	if (!table[idx])
	{
		while (i < idx)
			ft_memdel((void **)&table[i++]);
		ft_memdel((void **)&table);
	}
	return (table);
}

static char		**split(char const *s, char c, size_t count)
{
	char	**words_table;
	char	*str;

	while (*s == c)
		s++;
	str = ft_strchr(s, c);
	if (!str)
	{
		words_table = (char **)ft_memalloc(sizeof(char *)
							* (count + 1));
		if (words_table)
			words_table = set(words_table, count,
								ft_strsub(s, 0, ft_strlen(s)));
		if (words_table)
		{
			// TODO
			// CRASH !!
			//count += (*s) ? 1 : 0;
			words_table[count] = NULL;
		}
		return (words_table);
	}
	words_table = split(str, c, count + 1);
	if (words_table)
		words_table = set(words_table, count,
							ft_strsub(s, 0, ((uintptr_t)str - (uintptr_t)s)));
	return (words_table);
}

char			**ft_strsplit(char const *s, char c)
{
	return (split(s, c, 0));
}
