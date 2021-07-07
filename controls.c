#include "so_long.h"

int	ft_ternary(int yes, int i, int j)
{
	if (yes)
		return (i);
	else
		return (j);
}

/*
** Contact Exit - Mask Exit Image
**	Conditions are for light contact 
*/
void	ft_contact_exit(t_data *vars, struct s_pc *obj)
{
	int y;
	int x;
	static int m_x_up;
	static int m_y_up;
	int m_y;
	int m_x;

	y = obj->m_y1 / 32;
	x = obj->m_x1 / 32;
	m_x = m_x_up * 32;
	m_y = m_y_up * 32;
	ft_printf("x   :%d, y   :%d\nm_x1:%d, m_y2:%d\n", x, y, obj->m_x1/32, obj->m_y1/32);
	if (vars->matrix[y][x] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, obj->m_x1, obj->m_y1);
	else if (vars->matrix[y][m_x_up] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, m_x, obj->m_y1); // Prev Top right
	else if (vars->matrix[m_y_up][x] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, obj->m_x1, m_y); // Prev Bottom left
	else if (vars->matrix[m_y_up][m_x_up] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, m_x, m_y); // Prev Bottom right

	m_x_up = obj->x_up;
	m_y_up = obj->y_up;
}

/*
** m_x1 - 1st quadrant:
**	it's rounded down x coord
** m_x2 - 2nd quadrant: 
**  if pc didn't enter next left zone, no Q2, only cover Q1 and/or Q3
** m_y1 - 
** 	it's rounded down y coord
** m_y2 - 3rd quadrant:
**	if pc didn't enter next top zone, no Q3, only cover Q1 and/or Q2
*/
void	ft_cover_trails(t_data *vars, struct s_pc *obj)
{
	int mtx_y;
	int mtx_x;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->m_x1, obj->m_y1); // Prev Top left
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->m_x2, obj->m_y1); // Prev Top right
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->m_x1, obj->m_y2); // Prev Bottom left
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, obj->m_x2, obj->m_y2); // Prev Bottom right
	ft_contact_exit(vars, obj);
	mtx_x = obj->x / vars->pc_0.wth;
	mtx_y = obj->y / vars->pc_0.hgt;
	obj->m_x1 = mtx_x * vars->bg.wth; // New x_coord rounded down (for right movement)
	obj->m_x2 = ft_ternary((obj->x % vars->pc_0.wth == 0), mtx_x, mtx_x + 1);
	obj->m_x2 *=  vars->bg.wth;
	obj->m_y1 = mtx_y * vars->bg.hgt; // New y_coord rounded down (for down movement)
	obj->m_y2 = ft_ternary((obj->y % vars->pc_0.hgt == 0), mtx_y, mtx_y + 1);
	obj->m_y2 *= vars->bg.hgt;
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

bool	ft_contact_enemy(t_data *vars, struct s_pc pc, struct s_en en)
{
	bool a;
	bool b;
	bool c;
	bool d;

	a = ((pc.x > en.x) && (pc.x < (en.x + vars->en_0.wth)));
	b = (((pc.x + vars->pc_0.wth) > en.x) && ((pc.x + vars->pc_0.wth) < (en.x + vars->en_0.wth)));
	c = ((pc.y > en.y) && (pc.y < (en.y + vars->en_0.hgt)));
	d = (((pc.y + vars->pc_0.hgt) > en.y) && (pc.y + vars->pc_0.hgt < (en.y + vars->en_0.hgt)));
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

	// ft_printf(" Move Count: %d Items: %d", vars->pc.count, vars->items);
	// ft_printf(" y:%d x:%d \npc.y:%d \tpc.x:%d\n", y, x, vars->pc.y, vars->pc.x);
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

// void 	ft_put_sprites(t_data *vars, struct s_pc *pc)
// {
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc_0.ptr, vars->pc.x, vars->pc.y);
// }

/*
** Hooking intercepts functions calls, messages ot events
** keycode follows ASCII [prtinf("%d", keycode) for more]
*/
int		ft_wasd(int keycode, t_data *vars)
{
	int x;
	int y; //maybe remove?

	x = vars->pc.x / vars->pc_0.wth;
	y = vars->pc.y / vars->pc_0.hgt;
	// ft_printf("%d(%c)", keycode, keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if ((keycode == 119 || keycode == 115) && !vars->ended) // w / s
		y = ft_movement_pc(keycode, vars, &vars->pc);
	if ((keycode == 97 || keycode == 100) && !vars->ended) // a / d
		x = ft_movement_pc(keycode, vars, &vars->pc);
	else if(vars->ended)
		ft_printf("GAME OVER!!!\n");
	ft_data_log(vars, y, x);
	ft_cover_trails(vars, &vars->pc);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc_0.ptr, vars->pc.x, vars->pc.y);

	// ft_put_sprites(vars, &vars->pc);
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->pc_0.ptr, vars->pc.x , vars->pc.y);
	mlx_hook(vars->win, 2, 1L<<0, ft_wasd, vars); //similar to mlx_key_hook(vars->win, ft_wasd, vars) but now can hold;
	mlx_hook(vars->win, 17, 1L<<2, ft_redcross, vars);
	//mlx_mouse_hook(vars->win, ft_mouse, vars);
}