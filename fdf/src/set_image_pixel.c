/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:50:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/22 14:01:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void		set_image_pixel(t_mlx_sess * p, t_image *img, int color, int x, int y)
{
	int				opp;
	int				dec;
	unsigned char	*ptr;

	opp = img->bpp / 8;
	dec = opp;

	// TMP
	// Check if the point is inside the screen boundaries
	if (x < 0 || x > p->width || y < 0 || y > p->height)
		return;
	/*
	(void) x;
	('void) y;
	(void) color;
	(void) img;
	*/
	/*
	** TODO
	** manage different endians
	*/
	ptr = ((unsigned char *)img->data + y * img->sl) + x * opp;
	while (dec--)
		*(ptr + dec) = ((unsigned char *)(&color))[dec];

}
