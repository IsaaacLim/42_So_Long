#include "so_long.h"
#include "ft_printf.h"

/*
** Hooking intercepts functions calls, messages or events
** keycode follows ASCII [prtinf("%d", keycode) for more]
** 119: w | 115: s | 97: a | 100: d
**
** mlx_key_hook(vars->win, ft_wasd, vars); - one key press
** mlx_hook(vars->win, 2, 1L<<0, ft_wsad, vars); - variable mask, can hold key
**
** --- Commented out codes are for the project sharing session ---
**	To show what it looks like to constantly clear & rerender images on each
**	character movement
*/
static int	ft_wsad(int keycode, t_data *vars)
{
	int	y;
	int	x;

	y = vars->pc.y / vars->pc_0.hgt;
	x = vars->pc.x / vars->pc_0.wth;
	if (keycode == 65307)
		ft_close_window(vars);
	if ((keycode == 119 || keycode == 115) && !(vars->lost || vars->won))
		y = ft_move_pc(*vars, &vars->pc, keycode);
	if ((keycode == 97 || keycode == 100) && !(vars->lost || vars->won))
		x = ft_move_pc(*vars, &vars->pc, keycode);
	ft_contact_collectible(vars, vars->pc);
	ft_cover_trails(vars, &vars->pc);
	// mlx_clear_window(vars->mlx, vars->win); //to refresh screen
	// ft_map_img(vars); // to replace images on screen
	ft_put_sprites(*vars, vars->pc, keycode);
	if (vars->items == 0)
		ft_open_doors(*vars);
	if (vars->matrix[y][x] == 'E' && vars->items == 0)
		vars->won = true;
	if (!vars->lost && !vars->won)
		ft_printf("Moves: %d Items: %d\n", vars->pc.move_count, vars->items);
	else if (vars->lost)
		ft_printf("GAME OVER!!!\n");
	else if (vars->won)
		ft_printf("YOU WON with -%d- steps\n", vars->pc.move_count);
	return (0);
}

int	ft_control_hook(t_data *vars)
{
	int	x;
	int	y;

	x = vars->pc.x;
	y = vars->pc.y;
	vars->put_img(vars->mlx, vars->win, vars->pc_0.ptr, x, y);
	mlx_hook(vars->win, 2, (1L << 0), ft_wsad, vars);
	mlx_hook(vars->win, 17, (1L << 2), ft_close_window, vars);
	return (1);
}
