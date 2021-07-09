#include "so_long.h"

/*
** Simplified version of ft_movement. Only looks along its movement axis
** Use this function by parsing different code number to have diff movements
*/

static int	ft_move_up(t_data vars, struct s_en *en)
{
	int		y;
	int 	y_up;
	int 	x;
	char	*dir;

	dir = "adsd";
	y = (en->y - SPEED) / vars.en_0.hgt;
	x = en->x / vars.en_0.wth;
	if (ft_strchr("C1E", vars.matrix[y][x]))
	{
		en->dir = dir[en->rank % 4];
		return (en->y / vars.en_0.hgt);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.bg.ptr, en->m_x1, en->m_y1);
	y_up = ft_tco_int(((en->y - SPEED) % vars.en_0.hgt) == 0, y, y + 1);
	en->m_y1 = y_up * vars.en_0.hgt;
	return ((en->y -= SPEED) / vars.en_0.hgt);
}

static int	ft_move_left(t_data vars, struct s_en *en)
{
	int 	y;
	int 	x;
	int 	x_up;
	char	*dir;

	dir = "swds";
	y = en->y / vars.en_0.hgt;
	x = (en->x - SPEED) / vars.en_0.wth;
	if (ft_strchr("C1E", vars.matrix[y][x]))
	{
		en->dir = dir[en->rank % 4];
		return (en->x / vars.en_0.wth);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.bg.ptr, en->m_x1, en->m_y1);
	x_up = ft_tco_int(((en->x - SPEED) % vars.en_0.hgt) == 0, x, x + 1);
	en->m_x1 = x_up * vars.en_0.wth;
	return ((en->x -= SPEED) / vars.en_0.wth);
}

static int	ft_move_down(t_data vars, struct s_en *en)
{
	int 	y;
	int 	y_up;
	int 	x;
	char	*dir;

	dir = "daaw";
	y = (en->y + SPEED) / vars.en_0.hgt;
	y_up = ft_tco_int(((en->y + SPEED) % vars.en_0.hgt) == 0, y, y + 1);
	x = en->x / vars.en_0.wth;
	if (ft_strchr("C1E", vars.matrix[y_up][x]))
	{
		en->dir = dir[en->rank % 4];
		return (en->y / vars.en_0.hgt);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.bg.ptr, en->m_x1, en->m_y1);
	en->y += SPEED;
	en->m_y1 = en->y / vars.en_0.hgt * vars.en_0.hgt;
	return (y);
}

static int	ft_move_right(t_data vars, struct s_en *en)
{
	int		y;
	int		x;
	int		x_up;
	char	*dir;
	
	dir = "wswa";
	y = en->y / vars.en_0.hgt;
	x = (en->x + SPEED) / vars.en_0.wth;
	x_up = ft_tco_int(((en->x + SPEED) % vars.en_0.wth) == 0, x, x + 1);
	if (ft_strchr("C1E", vars.matrix[y][x_up]))
	{	
		en->dir = dir[en->rank % 4];
		return (en->x / vars.en_0.wth);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.bg.ptr, en->m_x1, en->m_y1);
	en->x += SPEED;
	en->m_x1 = en->x / vars.en_0.wth * vars.en_0.wth;
	return (x);
}

int	ft_movement_en(t_data vars, struct s_en *en)
{
	if (en->dir == 'w')
		return (ft_move_up(vars, en));
	else if (en->dir == 'a')
		return (ft_move_left(vars, en));
	else if (en->dir == 's')
		return (ft_move_down(vars, en));
	else if (en->dir == 'd')
		return (ft_move_right(vars, en));
	else
		return (-1);
}