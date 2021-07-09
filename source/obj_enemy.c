#include "so_long.h"

/*
** PLAYER CHARACTER CONTACT 
** Function is used under Enemy movement function, as it is running in a loop.
**	else if placed under Player movement, it won't execute without pc movement
** As both objects are moving, linear algebra is used
** 	(Finally made use of calculus 4 👨‍🎓)
** Conditions are made based on actual position of both objects,
**	rather than map coordinates.
*/
static bool	ft_contact_pc(t_data vars, struct s_en en, struct s_pc pc)
{
	bool	a;
	bool	b;
	bool	c;
	bool	d;

	a = ((pc.x > en.x) && (pc.x < (en.x + vars.en_0.wth)));
	b = (((pc.x + vars.pc_0.wth) > en.x)
			&& ((pc.x + vars.pc_0.wth) < (en.x + vars.en_0.wth)));
	c = ((pc.y > en.y) && (pc.y < (en.y + vars.en_0.hgt)));
	d = (((pc.y + vars.pc_0.hgt) > en.y)
			&& ((pc.y + vars.pc_0.hgt) < (en.y + vars.en_0.hgt)));
	if ((a || b) && (c || d))
		return (true);
	else if ((a || b) && pc.y == en.y)
		return (true);
	else if ((c || d) && pc.x == en.x)
		return (true);
	return (false);
}

/*
** As mlx_loop_hook calls this function rapidly,
**	< counter % speed == 0> is used to reduce the execution of enemy movement
** Function will monitor if any enemies contacted player character
** Enemy movement will stop if < lost || won > 
*/
static void	ft_en_move(t_data *vars, struct s_en *en)
{
	bool	lost;
	void	*en0;
	void	*en1;

	en0 = vars->en_0.ptr;
	en1 = vars->en_1.ptr;
	en->counter += 1;
	vars->put_img(vars->mlx, vars->win, en->img, en->x, en->y);
	if (en->counter % en->speed == 0 && !(vars->lost || vars->won))
	{
		en->img = ft_tco_voidStr(en->counter / SPEED % 2 == 0, en1, en0);
		ft_movement_en(*vars, en);
	}
	lost = ft_contact_pc(*vars, *en, vars->pc);
	if (lost)
		vars->lost = true;
}

/*
** Function is constantly ran by mlx_loop_hook
** Function activates up to 10 enemies,
**	depending if they are created from ft_create_enemy
*/
int	ft_en_loop(t_data *vars)
{
	if (vars->en1.rank == 1)
		ft_en_move(vars, &vars->en1);
	if (vars->en2.rank == 2)
		ft_en_move(vars, &vars->en2);
	if (vars->en3.rank == 3)
		ft_en_move(vars, &vars->en3);
	if (vars->en4.rank == 4)
		ft_en_move(vars, &vars->en4);
	if (vars->en5.rank == 5)
		ft_en_move(vars, &vars->en5);
	if (vars->en6.rank == 6)
		ft_en_move(vars, &vars->en6);
	if (vars->en7.rank == 7)
		ft_en_move(vars, &vars->en7);
	if (vars->en8.rank == 8)
		ft_en_move(vars, &vars->en8);
	if (vars->en9.rank == 9)
		ft_en_move(vars, &vars->en9);
	if (vars->en10.rank == 10)
		ft_en_move(vars, &vars->en10);
	return (1);
}

/*
** Initiates variables for activated enemy clones
*/
static void	ft_en_clone(t_data vars, struct s_en *en, int y, int x)
{
	static int	count;
	char		*dir;
	char		*speeds;
	char		**temp;
	int			i;

	count++;
	dir = "wsad";
	speeds = "433,283,71,97,119,661,151,109,43,947";
	temp = ft_split(speeds, ',');
	i = 0;
	en->rank = count;
	en->y = y * vars.en_0.hgt;
	en->x = x * vars.en_0.wth;
	en->m_y1 = y * vars.bg.hgt;
	en->m_x1 = x * vars.bg.wth;
	en->dir = dir[count % 4];
	en->counter = 1;
	en->speed = ft_atoi(temp[count - 1]);
	while (temp[i])
		i++;
	while (--i >= 0)
		free(temp[i]);
	free(temp);
	en->img = vars.en_0.ptr;
}

/*
** ENEMY CREATION
** Up to 10 enemies can be created
** Conditions are based on < ft_map_img >
*/
void	ft_create_enemy(t_data *vars, int y, int x)
{
	static int	count;

	count++;
	if (count > NUM_OF_ENEMIES)
		return ;
	else if (count == 1)
		ft_en_clone(*vars, &vars->en1, y, x);
	else if (count == 2)
		ft_en_clone(*vars, &vars->en2, y, x);
	else if (count == 3)
		ft_en_clone(*vars, &vars->en3, y, x);
	else if (count == 4)
		ft_en_clone(*vars, &vars->en4, y, x);
	else if (count == 5)
		ft_en_clone(*vars, &vars->en5, y, x);
	else if (count == 6)
		ft_en_clone(*vars, &vars->en6, y, x);
	else if (count == 7)
		ft_en_clone(*vars, &vars->en7, y, x);
	else if (count == 8)
		ft_en_clone(*vars, &vars->en8, y, x);
	else if (count == 9)
		ft_en_clone(*vars, &vars->en9, y, x);
	else if (count == 10)
		ft_en_clone(*vars, &vars->en10, y, x);
}
