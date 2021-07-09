#include "../so_long.h"

/*
** Open Exits when all collectibles are collected
*/
void	ft_open_doors(t_data vars)
{
	int	y;
	int	x;
	int	w;
	int	h;

	w = vars.ext1.wth;
	h = vars.ext1.hgt;
	y = -1;
	while (++y < vars.map_hgt)
	{
		x = -1;
		while (++x < vars.map_wth)
		{
			if (vars.matrix[y][x] == 'E')
				vars.put_img(vars.mlx, vars.win, vars.ext1.ptr, x * w, y * h);
		}
	}
}

/*
** Display steps counter on screen
** Called my mlx_loop_hook
*/
void	ft_put_steps(t_data vars)
{
	char	steps[12];
	char	*temp;
	int		i;
	int		j;

	j = ft_strlcpy(steps, "STEPS: 00000", 12);
	temp = ft_lltoa(vars.pc.move_count);
	i = 0;
	while (temp[i])
		i++;
	steps[j - 1] = temp[i - 1];
	while (--i >= 0)
		steps[--j] = temp[i];
	free(temp);
	vars.put_img(vars.mlx, vars.win, vars.sc.ptr, 8, 4);
	mlx_string_put(vars.mlx, vars.win, 16, 22, 0x006f235f, steps);
}

/*
** Helper function for ft_put_img
** Randomize Collectible display
*/
static void	ft_create_collectibles(t_data vars, int y, int x)
{
	static int		count;
	struct s_image	cl_0;
	struct s_image	cl_l;
	struct s_image	cl_r;

	cl_0 = vars.clt_0;
	cl_l = vars.clt_l;
	cl_r = vars.clt_r;
	if (count % 3 == 1)
		vars.put_img(vars.mlx, vars.win, cl_0.ptr, x * cl_0.wth, y * cl_0.hgt);
	else if (count % 3 == 2)
		vars.put_img(vars.mlx, vars.win, cl_l.ptr, x * cl_l.wth, y * cl_l.hgt);
	else
		vars.put_img(vars.mlx, vars.win, cl_r.ptr, x * cl_r.wth, y * cl_r.hgt);
	count++;
}

/*
** Helper function for ft_map_img
** Just to fit norminette row length / column width
*/
static void	ft_put_img(t_data *vars, int y, int x, int e)
{
	void			*mlx;
	void			*win;
	struct s_image	bg;
	struct s_image	wl;
	struct s_image	ext0;

	mlx = vars->mlx;
	win = vars->win;
	bg = vars->bg;
	wl = vars->wl;
	ext0 = vars->ext0;
	vars->put_img(mlx, win, bg.ptr, x * bg.wth, y * bg.hgt);
	if (vars->matrix[y][x] == '1')
		vars->put_img(mlx, win, wl.ptr, x * wl.wth, y * wl.hgt);
	else if (vars->matrix[y][x] == 'C')
		ft_create_collectibles(*vars, y, x);
	else if (vars->matrix[y][x] == 'E')
		vars->put_img(mlx, win, ext0.ptr, x * ext0.wth, y * ext0.hgt);
	else if (vars->matrix[y][x] == '0' && e % ENEMY_POSITION == 0)
		ft_create_enemy(vars, y, x);
}

/*
** CREATE MAP DISPLAY
** Player location is filled with background as it's possible to pass multiple
**  player postitions but only one Player Character will be made
*/
void	ft_map_img(t_data *vars)
{
	int	y;
	int	x;
	int	e;

	e = 0;
	y = -1;
	while (++y < vars->map_hgt)
	{	
		x = -1;
		while (++x < vars->map_wth)
		{
			ft_put_img(vars, y, x, e);
			e++;
		}
	}
}
