#include "so_long.h"

/*
** W & A
**  Check if new coord (ROUNDED DOWN) will hit a border with
**	other coord (rounded down) || other coord (rounded up)
** S & D
**	Check if new coord (ROUNDED UP) will hit a border with:
**	other coord (rounded down) || other coord (rounded up)
*/

static int	ft_move_up(t_data *vars, struct s_img *obj)
{
	int x;
	int	y;

	x = obj->x / obj->wth;
	y = (obj->y - SPEED) / obj->hgt;
	if (vars->matrix[y][x] == '1' || vars->matrix[y][obj->x_up] == '1')
		return (obj->y / obj->hgt);
	else
		obj->count++;
	obj->y -= SPEED;
	obj->y_up = ft_ternary((obj->y % obj->hgt) == 0, y, y + 1);
	return (y);
}

static int	ft_move_left(t_data *vars, struct s_img *obj)
{
	int y;
	int x;
	
	y = obj->y / obj->hgt;
	x = (obj->x - SPEED) / obj->wth;
	if (vars->matrix[y][x] == '1' || vars->matrix[obj->y_up][x] == '1')
		return ((obj->x) / obj->wth);
	else
		obj->count++;
	obj->x -= SPEED;
	obj->x_up = ft_ternary((obj->x % obj->wth) == 0, x, x + 1); 
	return (x);
}

static int	ft_move_down(t_data *vars, struct s_img *obj)
{
	int y;
	int y_up;
	int x;

	y = (obj->y + SPEED) / obj->hgt;
	y_up = ft_ternary(((obj->y + SPEED) % obj->hgt) == 0, y, y + 1);
	x = obj->x / obj->wth;
	if (vars->matrix[y_up][x] == '1' || vars->matrix[y_up][obj->x_up] == '1')
		return (obj->y / obj->hgt);
	else
		obj->count++;
	obj->y += SPEED;
	obj->y_up = y_up; 
	return (y);
}

static int	ft_move_right(t_data *vars, struct s_img *obj)
{
	int y;
	int x;
	int x_up;

	y = obj->y / obj->hgt;
	x = (obj->x + SPEED) / obj->wth;
	x_up = ft_ternary(((obj->x + SPEED) % obj->wth) == 0, x, x + 1);
	if (vars->matrix[y][x_up] == '1' || vars->matrix[obj->y_up][x_up] == '1')
		return (obj->x / obj->wth);
	else
		obj->count++;
	obj->x += SPEED;
	obj->x_up = x_up;
	return (x);
}

int	ft_movement_pc(int keycode, t_data *vars, struct s_img *obj)
{
	if (keycode == 'w')
		return (ft_move_up(vars, obj));
	else if (keycode == 'a')
		return (ft_move_left(vars, obj));
	else if (keycode == 's')
		return (ft_move_down(vars, obj));
	else if (keycode == 'd')
		return (ft_move_right(vars, obj));
}