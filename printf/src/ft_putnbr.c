/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/15 19:38:32 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		printbr(int n)
{
	if (n >= 10)
		printbr(n / 10);
	ft_putchar((n % 10) + '0');
}

static void		print_min(int64_t n)
{
	n = -n;
	if (n >= 10)
		printbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == INT_MIN)
			print_min((int64_t)n);
		else
			printbr(-n);
	}
	else
		printbr(n);
}