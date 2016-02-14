/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 20:14:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_putendl(char const *s)
{
	if (!s)
	{
		ft_putendl("ft_putendl returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	ft_putstr(s);
	write(1, "\n", 1);
}

#else

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
}
#endif
