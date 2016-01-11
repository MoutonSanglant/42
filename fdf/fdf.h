typedef struct	s_mlx_sess
{
	void	*sess;
	void	*win;
}				t_mlx_sess;

typedef struct	s_vector3
{
	int		x;
	int		y;
	int		z;
}				t_vector3;

void	draw_line(t_mlx_sess *, t_vector3, t_vector3);

void	draw_3dgrid(t_mlx_sess *);
