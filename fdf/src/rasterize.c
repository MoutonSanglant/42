/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:41:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/29 04:53:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <limits.h>

static float	edge_function(const t_vec3f *a, const t_vec3f *b, const t_vec3f *c)
{
	return ((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x));
}

static float	min3(const float *a, const float *b, const float *c)
{
	return (fminf(*a, fminf(*b, *c)));
}

static float	max3(const float *a, const float *b, const float *c)
{
	return (fmaxf(*a, fmaxf(*b, *c)));
}

void		rasterize(t_mlx_sess *p, t_tri *triangle)
{
	float	area;
	float xmin;
	float xmax;
	float ymin;
	float ymax;

	// get bouding box of the triangle
	xmin = min3(&(*triangle)[0].coord.x, &(*triangle)[1].coord.x, &(*triangle)[2].coord.x);
	xmax = max3(&(*triangle)[0].coord.x, &(*triangle)[1].coord.x, &(*triangle)[2].coord.x);
	ymin = min3(&(*triangle)[0].coord.y, &(*triangle)[1].coord.y, &(*triangle)[2].coord.y);
	ymax = max3(&(*triangle)[0].coord.y, &(*triangle)[1].coord.y, &(*triangle)[2].coord.y);

	if (xmin > p->width - 1 || xmax < 0 || ymin > p->height - 1 || ymax < 0)
		return;

	uint32_t x0 = (uint32_t)fmaxf(0.f, (float) floor(xmin));
	uint32_t x1 = (uint32_t)fminf(p->width - 1, (float) floor(xmax));
	uint32_t y0 = (uint32_t)fmaxf(0.f, (float) floor(ymin));
	uint32_t y1 = (uint32_t)fminf(p->height - 1, (float) floor(ymax));

	// check if vertex pass the top-left rule
	// - not implemented

	//triangle[0] = ...;
	//triangle[1] = ...;
	//triangle[2] = ...;

	area = edge_function(&(*triangle)[0].coord, &(*triangle)[1].coord, &(*triangle)[2].coord); // area of the full triangle * 2

	uint32_t x, y;
	y = y0;
	while (y < y1)
	{
		y++;
		x = x0;
		while (x < x1)
		{
			t_vec3f pixel_sample;
			float	w[3];

			x++;
			pixel_sample.x = x + .0f;
			pixel_sample.y = y + .0f;
			pixel_sample.z = 0;

			w[0] = edge_function(&(*triangle)[1].coord, &(*triangle)[2].coord, &pixel_sample); // signed area of the small triangle * 2
			w[1] = edge_function(&(*triangle)[2].coord, &(*triangle)[0].coord, &pixel_sample);
			w[2] = edge_function(&(*triangle)[0].coord, &(*triangle)[1].coord, &pixel_sample);

			if (w[0] >= 0.f && w[1] >= 0.f && w[2] >= 0.f)
			{
				float z;
				float oneOverZ;

				w[0] /= area;
				w[1] /= area;
				w[2] /= area;

				oneOverZ = (*triangle)[0].coord.z * w[0] + (*triangle)[1].coord.z * w[1] + (*triangle)[2].coord.z * w[2];
				z = 1 / oneOverZ;
				if (z < p->zbuffer[x + y * p->width])
				{
					p->zbuffer[x + y * p->width] = z;

					unsigned char r = w[0] * (*triangle)[0].color.r + w[1] * (*triangle)[1].color.r + w[2] * (*triangle)[2].color.r;
					unsigned char g = w[0] * (*triangle)[0].color.g + w[1] * (*triangle)[1].color.g + w[2] * (*triangle)[2].color.g;
					unsigned char b = w[0] * (*triangle)[0].color.b + w[1] * (*triangle)[1].color.b + w[2] * (*triangle)[2].color.b;

					//r *= z;
					//g *= z;
					//b *= z;
					//unsigned char g = w[0] * 0 + w[1] * 255 + w[2] * 0;
					//unsigned char b = w[0] * 0 + w[1] * 0 + w[2] * 255;

					int col = (r << 16) | (g << 8) | (b);

					set_image_pixel(p, p->img, mlx_get_color_value(p->sess, col), x, y);
				}
			}
		}
	}
}