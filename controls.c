#include "so_long.h"

/*
** Keypress will close window
*/
void	ft_close_window(t_data *vars)
{
	printf("\n");
	mlx_destroy_image(vars->mlx, vars->en.ptr);
	mlx_destroy_image(vars->mlx, vars->pc.ptr);
	mlx_destroy_image(vars->mlx, vars->bg.ptr);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}

void	ft_cover_trails(t_data *vars, int keycode)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, vars->bg.x, vars->bg.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, vars->bg.x2, vars->bg.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, vars->bg.x, vars->bg.y2);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, vars->bg.x2, vars->bg.y2);
	vars->bg.x = vars->pc.x / vars->bg.wth * vars->bg.wth;
	if (((vars->pc.x / vars->bg.wth + 1 ) * vars->bg.wth) < WIDTH)
		vars->bg.x2 = (vars->pc.x / vars->bg.wth + 1 ) * vars->bg.wth;
	else
		vars->bg.x2 = vars->bg.x;
	vars->bg.y = vars->pc.y / vars->bg.hgt * vars->bg.hgt;
	if (((vars->pc.y / vars->bg.hgt + 1) * vars->bg.hgt) < HEIGHT)
		vars->bg.y2 = (vars->pc.y / vars->bg.hgt + 1) * vars->bg.hgt;
	else
		vars->bg.y2 = vars->bg.y;
	//printf(" x1: %d, x2: %d y1: %d, y2: %d\n", vars->bg.x, vars->bg.x2, vars->bg.y2, vars->bg.y2);

}
void	ft_character(t_data *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x, vars->pc.y);
}

/*
** Hooking intercepts functions calls, messages ot events
** keycode follows ASCII [prtinf("%d", keycode) for more]
*/
int		ft_wasd(int keycode, t_data *vars)
{
	printf("key_hook: %d", keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if (keycode == 119 && vars->pc.y > 0) //w
		vars->pc.y -= 8;
	if (keycode == 97 && vars->pc.x > 0) //a
		vars->pc.x -= 8;
	if (keycode == 115 && vars->pc.y < (HEIGHT - vars->pc.hgt)) //s
		vars->pc.y += 8;
	if (keycode == 100 && vars->pc.x < (WIDTH - vars->pc.wth)) //d
		vars->pc.x += 8;
	printf("\tkey: %c pc.x: %d pc.y: %d\n", keycode, vars->pc.x, vars->pc.y);
	ft_cover_trails(vars, keycode);
	ft_character(vars);
	return (0);
}

int		ft_mouse(int button, int x, int y, t_data *vars)
{
	// int x;
	// int y;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	printf("pos:%d %d %d \n", button, x, y);
	//if (button == 1 && (x >= 593 && x <= 640) && (y >= -30 && y <= 0)) // 'X' postition
	if (button == 1 && (x >= 593 && x <= 640) && (y >= 20 && y <= 40)) // one block below 'X'
		ft_close_window(vars); //won't leak
	return (0);
}

int		ft_redcross(int keycode, t_data *vars)
{
	printf("\nButton Keycode: %d\n", keycode);
	//ft_close_window(vars); //seg fault with leaks
	//exit (0); // no seg fault but leaking
}

int		ft_control(t_data *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x, vars->pc.y);
	mlx_hook(vars->win, 2, 1L<<0, ft_wasd, vars); //similar to mlx_key_hook(vars->win, ft_wasd, vars);
	mlx_hook(vars->win, 17, 1L<<2, ft_redcross, vars);
	//mlx_mouse_hook(vars->win, ft_mouse, vars);
}