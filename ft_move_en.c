#include "so_long.h"

static int	ft_move_up(t_data *vars, struct s_img *obj, int code)
{
	int 	x;
	int		y;

	x = obj->x / obj->wth;
	y = (obj->y - SPEED) / obj->hgt;
	if (ft_strchr("C1E", vars->matrix[y][x]))
		return (obj->y / obj->hgt);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y1);
	obj->mask_y2 = ft_ternary(((obj->y - SPEED) % obj->hgt) == 0, y, y + 1);
	return ((obj->y -= SPEED) / obj->hgt);
}

static int	ft_move_left(t_data *vars, struct s_img *obj, int code)
{
	int 	y;
	int 	y_up;
	int 	x;
	char	crt;
	char	nxt;
	
	y = obj->y / obj->hgt;
	y_up = ft_ternary((obj->y % obj->hgt) == 0, y, y + 1);
	x = (obj->x - SPEED) / obj->wth;
	crt = vars->matrix[y][x];
	nxt = vars->matrix[y_up][x];
	if (ft_strchr("C1E", crt) || ft_strchr("C1E", nxt))
		return (obj->x / obj->wth);
	return ((obj->x -= SPEED) / obj->wth);
}

static int	ft_move_down(t_data *vars, struct s_img *obj, int code)
{
	int 	y;
	int 	y_up;
	int 	x;
	int 	x_up;
	char	crt;
	char	nxt;

	y = (obj->y + SPEED) / obj->hgt;
	y_up = ft_ternary(((obj->y + SPEED) % obj->hgt) == 0, y, y + 1);
	x = obj->x / obj->wth;
	x_up = ft_ternary((obj->x % obj->wth) == 0, x, x + 1);
	crt = vars->matrix[y_up][x];
	nxt = vars->matrix[y_up][x_up];
	if (ft_strchr("C1E", crt) || ft_strchr("C1E", nxt))
		return (obj->y / obj->hgt);
	return ((obj->y += SPEED) / obj->hgt);
}

static int	ft_move_right(t_data *vars, struct s_img *obj, int code)
{
	int		y;
	int		x;
	int		x_up;

	y = obj->y / obj->hgt;
	x = (obj->x + SPEED) / obj->wth;
	x_up = ft_ternary(((obj->x + SPEED) % obj->wth) == 0, x, x + 1);
	if (ft_strchr("C1E", vars->matrix[y][x_up]))
	{	
		if (code == 1)
			obj->dir = 'w';
		return (obj->x / obj->wth);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y1);
	obj->x += SPEED;
	obj->mask_x1 = obj->x / obj->wth * obj->wth;
	return (x);
}

int	ft_movement_en(t_data *vars, struct s_img *obj, int code)
{
	if (obj->dir == 'w')
		return (ft_move_up(vars, obj, code));
	else if (obj->dir == 'a')
		return (ft_move_left(vars, obj, code));
	else if (obj->dir == 's')
		return (ft_move_down(vars, obj, code));
	else if (obj->dir == 'd')
		return (ft_move_right(vars, obj, code));
}