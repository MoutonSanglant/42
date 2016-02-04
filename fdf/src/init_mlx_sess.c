/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_sess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:39:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/04 17:02:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	World, View & Projection matrices
**	---------------------------------
**		World_To_Camera is the inverse matric of View matrix,
**		it is precomputed to save up process time
**	---------------------------------
**		Camera needs to look down (along the negative 'Z-axis')
*/

static void	init_matrices(t_mlx_sess *sess)
{
	t_mat4x4	trans;

	sess->world = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	sess->view = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	sess->projection = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	sess->world_to_camera = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4));
	identity_matrix4(sess->world);
	identity_matrix4(sess->view);
	identity_matrix4(sess->projection);
	identity_matrix4(sess->world_to_camera);

	rotation_x_matrix4(&trans, RAD(90));
	matrix4_product(&trans, sess->view);
	inverse_matrix4(sess->view, sess->world_to_camera);
}

static void	init_camera(t_mlx_sess *sess)
{
	sess->camera.aspect = (float)sess->width / (float)sess->height;
	sess->camera.angle_of_view = 90.f;
	sess->camera.near = .1f;
	sess->camera.far = 100.f;
	sess->camera.right = .1f * sess->camera.aspect;
	sess->camera.top = .1f;
	sess->camera.left = -sess->camera.right;
	sess->camera.bottom = -sess->camera.top;
	set_perspective_camera(sess);
}

static void	draw_settings(t_mlx_sess *sess)
{
	sess->bresenham = 1;
	sess->line_width = .06f;
	sess->lines_color = 0x00000000;
	sess->bg_color = 0x00046000;
	//sess->faces_color = sess->bg_color;
	sess->faces_color = 0x00ff0000;
}

/*
**	return
**	1: system is big-endian
**	0: system is little-endian
*/
static int	get_system_endian()
{
	int		a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return(1);
	else
		return(0);
}

t_mlx_sess	*init_mlx_sess(int width, int height)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)ft_memalloc(sizeof(t_mlx_sess));
	if (!(sess->sess = mlx_init()))
	{
		ft_memdel((void **)&sess);
		alloc_error("sess->sess", sizeof(t_mlx_sess));
	}
	sess->width = width;
	sess->height = height;
	if (!(sess->win = mlx_new_window(sess->sess, sess->width, sess->height, "test_mlx")))
	{
		ft_memdel((void **)&sess);
		alloc_error("sess->win", sizeof(int) * sess->width * sess->height);
	}
	sess->need_update = 1;
	sess->last_tval.tv_sec = 0;
	sess->last_tval.tv_usec = 0;
	sess->system_endian = get_system_endian();
	init_matrices(sess);
	init_camera(sess);
	draw_settings(sess);
	return (sess);
}