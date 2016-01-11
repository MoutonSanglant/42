#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <includes/libft.h>
#include "mlx.h"
#include "fdf.h"
//#include "mlx_int.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*mlx_sess;

	mlx_sess = (t_mlx_sess *)p;
	if (key == 53)
	{
		mlx_destroy_window(mlx_sess->sess, mlx_sess->win);
		free(mlx_sess);
		exit(0);
	}
	return (0);
}

int		loop(void *p)
{
	draw_3dgrid((t_mlx_sess *)p);
	//draw_line((t_mlx_sess *)p);
	//draw_picture((t_mlx_sess *)p);

	return (0);
}

int		main()
{
	t_mlx_sess	*param;

	param = (t_mlx_sess *)malloc(sizeof(t_mlx_sess));
	if (!(param->sess = mlx_init()))
	{
		free(param);
		return (1);
	}
	if (!(param->win = mlx_new_window(param->sess, 400, 400, "test_mlx")))
	{
		free(param);
		return (1);
	}

	mlx_key_hook(param->win, &keypress, (void *)param);
	mlx_loop_hook(param->sess, &loop, (void *)param);
	mlx_loop(param->sess);

	return (0);
}
