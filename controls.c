#include "so_long.h"

void	ft_cover_trails(t_data *vars, struct s_img *chr)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, chr->mask_x1, chr->mask_y1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, chr->mask_x2, chr->mask_y1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, chr->mask_x1, chr->mask_y2);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, chr->mask_x2, chr->mask_y2);
	chr->mask_x1 = chr->x / vars->bg.wth * vars->bg.wth;
	if (((chr->x / vars->bg.wth + 1 ) * vars->bg.wth) < vars->win_wth)
		chr->mask_x2 = (chr->x / vars->bg.wth + 1 ) * vars->bg.wth;
	else
		chr->mask_x2 = vars->bg.x;
	chr->mask_y1 = chr->y / vars->bg.hgt * vars->bg.hgt;
	if (((chr->y / vars->bg.hgt + 1) * vars->bg.hgt) < vars->win_hgt)
		chr->mask_y2 = (chr->y / vars->bg.hgt + 1) * vars->bg.hgt;
	else
		chr->mask_y2 = chr->mask_y1;
}

void	ft_character(t_data *vars)
{
	ft_cover_trails(vars, &vars->pc);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x, vars->pc.y);
}

/*
** Hooking intercepts functions calls, messages ot events
** keycode follows ASCII [prtinf("%d", keycode) for more]
*/
int		ft_wasd(int keycode, t_data *vars)
{
	ft_printf("key_hook: %d", keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if (keycode == 119 && vars->pc.y > 0) //w
		vars->pc.y -= 8;
	if (keycode == 97 && vars->pc.x > 0) //a
		vars->pc.x -= 8;
	if (keycode == 115 && vars->pc.y < (vars->win_hgt - vars->pc.hgt)) //s
		vars->pc.y += 8;
	if (keycode == 100 && vars->pc.x < (vars->win_wth - vars->pc.wth)) //d
		vars->pc.x += 8;
	ft_printf("\tkey: %c pc.x: %d pc.y: %d\n", keycode, vars->pc.x, vars->pc.y);
	ft_character(vars);
	return (0);
}

int		ft_mouse(int button, int x, int y, t_data *vars)
{
	// int x;
	// int y;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	ft_printf("pos:%d %d %d \n", button, x, y);
	//if (button == 1 && (x >= 593 && x <= 640) && (y >= -30 && y <= 0)) // 'X' postition
	if (button == 1 && (x >= 593 && x <= 640) && (y >= 20 && y <= 40)) // one block below 'X'
		ft_close_window(vars); //won't leak
	return (0);
}

int		ft_redcross(int keycode, t_data *vars)
{
	ft_printf("\nButton Keycode: %d\n", keycode);
	//ft_close_window(vars); //seg fault with leaks
	//exit (0); // no seg fault but leaking
}

int		ft_control(t_data *vars)
{
	vars->pc.x *= vars->bg.wth;
	vars->pc.y *= vars->bg.hgt;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x , vars->pc.y);
	mlx_hook(vars->win, 2, 1L<<0, ft_wasd, vars); //similar to mlx_key_hook(vars->win, ft_wasd, vars) but now can hold;
	mlx_hook(vars->win, 17, 1L<<2, ft_redcross, vars);
	//mlx_mouse_hook(vars->win, ft_mouse, vars);
}