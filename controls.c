#include "so_long.h"

int	ft_ternary(int yes, int i, int j)
{
	if (yes)
		return (i);
	else
		return (j);
}


void	ft_cover_trails(t_data *vars, struct s_img *obj)
{
	int mtx_x;
	int mtx_y;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y1); // Prev Top left
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x2, obj->mask_y1); // Prev Top right
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y2); // Prev Bottom left
	if (obj->mask_bot_right)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x2, obj->mask_y2); // Prev Bottom right
	
	mtx_x = obj->x / obj->wth;
	mtx_y = obj->y / obj->hgt;
	obj->mask_bot_right = true;
	obj->mask_x1 = mtx_x * vars->bg.wth; // New x_coord rounded down (for right movement)
	
	/*
	** for left movement, if new x_coord rounded down + 1 != wall, cover up right side
	*/
	// obj->mask_x2 = ft_ternary(vars->matrix[mtx_y][mtx_x + 1] != '1', (mtx_x + 1) * vars->bg.wth, obj->mask_x1);
	if (ft_strchr("C1E", vars->matrix[mtx_y][mtx_x + 1]))
		obj->mask_x2 = obj->mask_x1;
	else
		obj->mask_x2 = (mtx_x + 1) * vars->bg.wth;
	obj->mask_y1 = mtx_y * vars->bg.hgt; // New y_coord rounded down (for down movement)
	
	/*
	** for up movement, if new y_coord rounded down + 1 != wall, cover up bottom
	*/
	// obj->mask_y2 = ft_ternary(vars->matrix[mtx_y + 1][mtx_x] != '1', (mtx_y + 1) * vars->bg.hgt, obj->mask_y1);
	if (ft_strchr("C1E", vars->matrix[mtx_y + 1][mtx_x]))
	{
		ft_printf(" block ");
		obj->mask_y2 = obj->mask_y1;
	}
	else
	{
		ft_printf(" free ");
		obj->mask_y2 = (mtx_y + 1) * vars->bg.hgt;
	}


	if (ft_strchr("C1E", vars->matrix[mtx_y + 1][mtx_x + 1])) // for Bottom right masking
		obj->mask_bot_right = false;
}

/*
** Contact Collectible (slight touch)
** 	if [y][x] == 'C'
	if [y][x_up]
	if [x_up][y]
	if [y_up][x_up]

*/
void	ft_data_log(t_data *vars, int y, int x)
{
	ft_printf(" Move Count: %d Items: %d", vars->pc.count, vars->items);
	ft_printf(" x:%d y:%d pc.x:%d pc.y:%d\n", x, y, vars->pc.x, vars->pc.y);
	if (vars->matrix[y][x] == 'C')
	{	
		vars->items--;
		vars->matrix[y][x] = '0';
	}
	if (vars->matrix[y][x] == 'E' && vars->items == 0)
	{
		ft_printf("EXITED IN -%d- steps\n", vars->pc.count);
		vars->ended = true;
	}

}
/*
** Hooking intercepts functions calls, messages ot events
** keycode follows ASCII [prtinf("%d", keycode) for more]
*/
int		ft_wasd(int keycode, t_data *vars)
{
	int x;
	int y;

	x = vars->pc.x / vars->pc.wth;
	y = vars->pc.y / vars->pc.hgt;
	ft_printf("%d(%c)", keycode, keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if ((keycode == 119 || keycode == 115) && !vars->ended) // w / s
		y = ft_movement(keycode, vars, &vars->pc);
	if ((keycode == 97 || keycode == 100) && !vars->ended) // a / d
		x = ft_movement(keycode, vars, &vars->pc);
	ft_cover_trails(vars, &vars->pc);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x, vars->pc.y);
	ft_data_log(vars, y, x);
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
	vars->pc.x *= vars->pc.wth;
	vars->pc.y *= vars->pc.hgt;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x , vars->pc.y);
	mlx_hook(vars->win, 2, 1L<<0, ft_wasd, vars); //similar to mlx_key_hook(vars->win, ft_wasd, vars) but now can hold;
	mlx_hook(vars->win, 17, 1L<<2, ft_redcross, vars);
	//mlx_mouse_hook(vars->win, ft_mouse, vars);
}