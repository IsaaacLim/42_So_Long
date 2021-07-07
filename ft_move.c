#include "so_long.h"

/*
** W & A
**  Check if new coord (ROUNDED DOWN) will hit a border with
**	other coord (rounded down) || other coord (rounded up)
** S & D
**	Check if new coord (ROUNDED UP) will hit a border with:
**	other coord (rounded down) || other coord (rounded up)
*/

static int	ft_move_up(t_data *vars, struct s_pc *obj)
{
	int x;
	int	y;

	x = obj->x / vars->pc_r1.wth; //make b1/b2
	y = (obj->y - SPEED) / vars->pc_r1.hgt;
	if (vars->matrix[y][x] == '1' || vars->matrix[y][obj->x_up] == '1')
		return (obj->y / vars->pc_r1.hgt);
	else
		obj->count++;
	obj->y -= SPEED;
	obj->y_up = ft_ternary((obj->y % vars->pc_r1.hgt) == 0, y, y + 1);
	return (y);
}

static int	ft_move_left(t_data *vars, struct s_pc *obj)
{
	int y;
	int x;
	
	y = obj->y / vars->pc_r1.hgt;
	x = (obj->x - SPEED) / vars->pc_r1.wth;
	if (vars->matrix[y][x] == '1' || vars->matrix[obj->y_up][x] == '1')
		return ((obj->x) / vars->pc_r1.wth);
	else
		obj->count++;
	obj->x -= SPEED;
	obj->x_up = ft_ternary((obj->x % vars->pc_r1.wth) == 0, x, x + 1); 
	return (x);
}

static int	ft_move_down(t_data *vars, struct s_pc *obj)
{
	int y;
	int y_up;
	int x;

	y = (obj->y + SPEED) / vars->pc_r1.hgt;
	y_up = ft_ternary(((obj->y + SPEED) % vars->pc_r1.hgt) == 0, y, y + 1);
	x = obj->x / vars->pc_r1.wth;
	if (vars->matrix[y_up][x] == '1' || vars->matrix[y_up][obj->x_up] == '1')
		return (obj->y / vars->pc_r1.hgt);
	else
		obj->count++;
	obj->y += SPEED;
	obj->y_up = y_up; 
	return (y);
}

static int	ft_move_right(t_data *vars, struct s_pc *obj)
{
	int y;
	int x;
	int x_up;

	y = obj->y / vars->pc_r1.hgt;
	x = (obj->x + SPEED) / vars->pc_r1.wth;
	x_up = ft_ternary(((obj->x + SPEED) % vars->pc_r1.wth) == 0, x, x + 1);
	if (vars->matrix[y][x_up] == '1' || vars->matrix[obj->y_up][x_up] == '1')
		return (obj->x / vars->pc_r1.wth);
	else
		obj->count++;
	obj->x += SPEED;
	obj->x_up = x_up;
	return (x);
}

int	ft_movement_pc(int keycode, t_data *vars, struct s_pc *obj)
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