#include "so_long.h"
#include "libft.h"

/*
** W & A
**  Check if new coord (ROUNDED DOWN) will hit a border with
**	other coord (rounded down) || other coord (rounded up)
** S & D
**	Check if new coord (ROUNDED UP) will hit a border with:
**	other coord (rounded down) || other coord (rounded up)
**
** --- Commented out codes are for the project sharing session ---
** To show what it looks like to manually cover image trails with:
**	- background covering character's previous (nearest) map position
*8	- background covering charactor's previous actual position 
*/

static int	ft_move_up(t_data vars, struct s_pc *pc)
{
	int	x;
	int	y;

	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x, pc->y_up * 32); //manual mask_absolute
	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x, pc->y); //manual mask_relative
	x = pc->x / vars.pc_0.wth;
	y = (pc->y - SPEED) / vars.pc_0.hgt;
	if (vars.matrix[y][x] == '1' || vars.matrix[y][pc->x_up] == '1')
		return (pc->y / vars.pc_0.hgt);
	pc->move_count++;
	pc->y -= SPEED;
	pc->y_up = ft_tco_int((pc->y % vars.pc_0.hgt) == 0, y, y + 1);
	return (y);
}

static int	ft_move_left(t_data vars, struct s_pc *pc)
{
	int	y;
	int	x;

	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x_up * 32, pc->y); //manual mask_absolute
	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x + 24, pc->y); //manual mask_relative
	y = pc->y / vars.pc_0.hgt;
	x = (pc->x - SPEED) / vars.pc_0.wth;
	if (vars.matrix[y][x] == '1' || vars.matrix[pc->y_up][x] == '1')
		return ((pc->x) / vars.pc_0.wth);
	pc->move_count++;
	pc->x -= SPEED;
	pc->x_up = ft_tco_int((pc->x % vars.pc_0.wth) == 0, x, x + 1);
	return (x);
}

static int	ft_move_down(t_data vars, struct s_pc *pc)
{
	int	y;
	int	y_up;
	int	x;

	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x, pc->y /32*32); //manual mask_absolute
	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x, pc->y); //manual mask_relative
	y = (pc->y + SPEED) / vars.pc_0.hgt;
	y_up = ft_tco_int(((pc->y + SPEED) % vars.pc_0.hgt) == 0, y, y + 1);
	x = pc->x / vars.pc_0.wth;
	if (vars.matrix[y_up][x] == '1' || vars.matrix[y_up][pc->x_up] == '1')
		return (pc->y / vars.pc_0.hgt);
	pc->move_count++;
	pc->y += SPEED;
	pc->y_up = y_up;
	return (y);
}

static int	ft_move_right(t_data vars, struct s_pc *pc)
{
	int	y;
	int	x;
	int	x_up;

	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x /32*32, pc->y); //manual mask_absolute
	// vars.put_img(vars.mlx, vars.win, vars.en_0.ptr, pc->x - 24, pc->y); //manual mask_relative
	y = pc->y / vars.pc_0.hgt;
	x = (pc->x + SPEED) / vars.pc_0.wth;
	x_up = ft_tco_int(((pc->x + SPEED) % vars.pc_0.wth) == 0, x, x + 1);
	if (vars.matrix[y][x_up] == '1' || vars.matrix[pc->y_up][x_up] == '1')
		return (pc->x / vars.pc_0.wth);
	pc->move_count++;
	pc->x += SPEED;
	pc->x_up = x_up;
	return (x);
}

int	ft_move_pc(t_data vars, struct s_pc *pc, int keycode)
{
	if (keycode == 'w')
		return (ft_move_up(vars, pc));
	else if (keycode == 'a')
		return (ft_move_left(vars, pc));
	else if (keycode == 's')
		return (ft_move_down(vars, pc));
	else if (keycode == 'd')
		return (ft_move_right(vars, pc));
	else
		return (-1);
}
