#include "so_long.h"

/*
** Initiates struct variables
**	PC - actual values
**	EN - Empty values (not all clones will be used)
**	also other struct variables
*/
static void	ft_init_pc(t_data vars, struct s_pc *pc)
{
	int		x;
	int		y;
	int		wth;
	int		hgt;
	char	**matrix;

	x = pc->x;
	y = pc->y;
	wth = vars.bg.wth;
	hgt = vars.bg.hgt;
	matrix = vars.matrix;
	pc->x_up = x;
	pc->y_up = y;
	pc->m_x1 = x * wth;
	pc->m_x2 = ft_tco_int(matrix[y][x + 1] != '1', (x + 1) * wth, pc->m_x1);
	pc->m_y1 = y * hgt;
	pc->m_y2 = ft_tco_int(matrix[y + 1][x] != '1', (y + 1) * hgt, pc->m_y1);
	pc->move_count = 0;
	pc->x *= vars.pc_0.wth;
	pc->y *= vars.pc_0.hgt;
}

static void	ft_init_en_clone(struct s_en *en)
{
	en->x = -1;
	en->y = -1;
	en->m_x1 = -1;
	en->m_y1 = -1;
	en->dir = 'q';
	en->rank = -1;
	en->counter = -1;
	en->speed = -1;
	en->img = NULL;
}

static void	ft_init_en(t_data *vars)
{
	ft_init_en_clone(&vars->en1);
	ft_init_en_clone(&vars->en2);
	ft_init_en_clone(&vars->en3);
	ft_init_en_clone(&vars->en4);
	ft_init_en_clone(&vars->en5);
	ft_init_en_clone(&vars->en6);
	ft_init_en_clone(&vars->en7);
	ft_init_en_clone(&vars->en8);
	ft_init_en_clone(&vars->en9);
	ft_init_en_clone(&vars->en10);
}

void	ft_init_vars(t_data *vars)
{
	vars->lost = false;
	vars->won = false;
	vars->win_wth = vars->map_wth * vars->bg.wth;
	vars->win_hgt = vars->map_hgt * vars->bg.hgt;
	ft_init_en(vars);
	ft_init_pc(*vars, &vars->pc);
}
