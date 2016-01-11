#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <includes/libft.h>
#include "mlx.h"
//#include "mlx_int.h"

typedef struct	s_mlx_sess
{
	void	*sess;
	void	*win;
}				t_mlx_sess;

int		keypress(int key, void *p)
{
	t_mlx_sess	*mlx_sess;

	mlx_sess = (t_mlx_sess *)p;
	if (key == 53)
	{
		free(p);
		mlx_destroy_window(mlx_sess->sess, mlx_sess->win);
		exit(0);
	}
	return (0);
}

void	draw_pixel_chain(t_mlx_sess *mlx_sess)
{
	static int	x = 0;
	static int	y = 0;
	static int	r = 0;
	static int	g = 0;
	static int	b = 0;
	int			c;

	c = r | g | b;
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x, y, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x + 1, y, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x, y + 1, c);
	mlx_pixel_put(mlx_sess->sess, mlx_sess->win, x + 1, y + 1, c);
	x += 2;
	if (x >= 199)
	{
		y += 2;
		x = 0;
		if (y >= 199)
			y = 0;
	}
	r += 0x00000001;
	g += 0x00000200;
	b += 0x00080000;
}

void	draw_picture(t_mlx_sess *mlx_sess)
{
	static void		*img = NULL;
	static int		x = 0;
	static int		y = 0;

	if (!img)
	{
		//img = mlx_new_image(mlx_sess->sess, x, y);
		img = mlx_xpm_file_to_image(mlx_sess->sess, "./img.xpm", &x, &y);
	}
	mlx_clear_window(mlx_sess->sess, mlx_sess->win);
	mlx_put_image_to_window(mlx_sess->sess, mlx_sess->win, img, 0, 0);
	mlx_string_put(mlx_sess->sess, mlx_sess->win, 0, 0, 0x00ff0000, "Hello");
}

int		loop(void *p)
{
	//draw_pixel_chain((t_mlx_sess *)p);
	draw_picture((t_mlx_sess *)p);

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
