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
	int mtx_y;
	int mtx_x;

	mtx_y = obj->mask_y1 / obj->hgt;
	mtx_x = obj->mask_x1 / obj->wth;
	if (vars->matrix[mtx_y][mtx_x] != 'E')//if top left door
		mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y1); // Prev Top left
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, obj->mask_x1, obj->mask_y1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x2, obj->mask_y1); // Prev Top right
	if (vars->matrix[obj->mask_y2 / obj->hgt][mtx_x] != 'E') //if bottom left door
		mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x1, obj->mask_y2); // Prev Bottom left
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, obj->mask_x1, obj->mask_y2);
	if (obj->mask_bot_right)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->mask_x2, obj->mask_y2); // Prev Bottom right
	
	mtx_x = obj->x / obj->wth;
	mtx_y = obj->y / obj->hgt;
	obj->mask_bot_right = true;
	// if (vars->matrix[mtx_y][mtx_x] != 'E')
	obj->mask_x1 = mtx_x * vars->bg.wth; // New x_coord rounded down (for right movement)
	/*
	** for left movement, if new x_coord rounded down + 1 != wall, cover up right side
	*/
	if (ft_strchr("C1E", vars->matrix[mtx_y][mtx_x + 1]))
		obj->mask_x2 = obj->mask_x1;
	else
		obj->mask_x2 = (mtx_x + 1) * vars->bg.wth;
	
	obj->mask_y1 = mtx_y * vars->bg.hgt; // New y_coord rounded down (for down movement)
	/*
	** for up movement, if new y_coord rounded down + 1 != wall, cover up bottom
	*/
	if (ft_strchr("C1E", vars->matrix[mtx_y + 1][mtx_x]))
		obj->mask_y2 = obj->mask_y1;
	else
		obj->mask_y2 = (mtx_y + 1) * vars->bg.hgt;
	if (ft_strchr("C1E", vars->matrix[mtx_y + 1][mtx_x + 1])) // for Bottom right masking
		obj->mask_bot_right = false;
}

/*
** Contact Collectible
**	Conditions are for light contact 
*/
void	ft_contact_collectible(t_data *vars, int y, int x)
{
	if (vars->matrix[y][x] == 'C')
		vars->matrix[y][x] = '0';
	else if (vars->matrix[y][vars->pc.x_up] == 'C')
		vars->matrix[y][vars->pc.x_up] = '0';
	else if (vars->matrix[vars->pc.y_up][x] == 'C')
		vars->matrix[vars->pc.y_up][x] = '0';
	else if (vars->matrix[vars->pc.y_up][vars->pc.x_up] == 'C')
		vars->matrix[vars->pc.y_up][vars->pc.x_up] = '0';
	else
		return ;
	vars->items--;
}

bool	ft_contact_enemy(t_data *vars, struct s_img pc, struct s_img en)
{
	bool a;
	bool b;
	bool c;
	bool d;

	a = ((pc.x > en.x) && (pc.x < (en.x + vars->en.wth)));
	b = (((pc.x + pc.wth) > en.x) && ((pc.x + pc.wth) < (en.x + vars->en.wth)));
	c = ((pc.y > en.y) && (pc.y < (en.y + vars->en.hgt)));
	d = (((pc.y + pc.hgt) > en.y) && (pc.y + pc.hgt < (en.y + vars->en.hgt)));
	if ((a || b) && (c || d))
		return (true);
	else if ((a || b) && pc.y == en.y)
		return (true);
	else if ((c || d) && pc.x == en.x)
		return (true);
	else
		return (false);
}

void	ft_data_log(t_data *vars, int y, int x)
{
	bool gameover;

	ft_printf(" Move Count: %d Items: %d", vars->pc.count, vars->items);
	ft_printf(" y:%d x:%d \npc.y:%d \tpc.x:%d\n", y, x, vars->pc.y, vars->pc.x);
	ft_contact_collectible(vars, y, x);
	// gameover = ft_contact_enemy(vars, vars->pc, vars->en);
	// if (gameover)
	// {
	// 	ft_printf("GAME OVER\n");
	// 	vars->ended = true;
	// }
	if (vars->matrix[y][x] == 'E' && vars->items == 0)
	{
		ft_printf("YOU WON with -%d- steps\n", vars->pc.count);
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
	int y; //maybe remove?

	x = vars->pc.x / vars->pc.wth;
	y = vars->pc.y / vars->pc.hgt;
	ft_printf("%d(%c)", keycode, keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if ((keycode == 119 || keycode == 115) && !vars->ended) // w / s
		y = ft_movement_pc(keycode, vars, &vars->pc);
	if ((keycode == 97 || keycode == 100) && !vars->ended) // a / d
		x = ft_movement_pc(keycode, vars, &vars->pc);
	ft_data_log(vars, y, x);
	ft_cover_trails(vars, &vars->pc);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc.ptr, vars->pc.x, vars->pc.y);
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