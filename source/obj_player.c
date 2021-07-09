#include "../so_long.h"

/*
** PLAYER CHARACTER SPRITES
** Determines which direction the character is facing
**	then put relevant sprites
*/
void 	ft_put_sprites(t_data vars, struct s_pc pc, int keycode)
{
	static int	steps;
	void		*img_w;
	void		*img_s;
	void		*img_a;
	void		*img_d;

	steps += 1;
	img_w = ft_tco_voidStr(steps % 2 == 0, vars.pc_w1.ptr, vars.pc_w2.ptr);
	img_d = ft_tco_voidStr(steps % 2 == 0, vars.pc_d1.ptr, vars.pc_d2.ptr);
	img_s = ft_tco_voidStr(steps % 2 == 0, vars.pc_s1.ptr, vars.pc_s2.ptr);
	img_a = ft_tco_voidStr(steps % 2 == 0, vars.pc_a1.ptr, vars.pc_a2.ptr);
	if (keycode == 'w')
		vars.put_img(vars.mlx, vars.win, img_w, pc.x, pc.y);
	else if (keycode == 's')
		vars.put_img(vars.mlx, vars.win, img_s, pc.x, pc.y);
	else if (keycode == 'a')
		vars.put_img(vars.mlx, vars.win, img_a, pc.x, pc.y);
	else if (keycode == 'd')
		vars.put_img(vars.mlx, vars.win, img_d, pc.x, pc.y);
	else
		vars.put_img(vars.mlx, vars.win, vars.pc_0.ptr, pc.x, pc.y);
}

/*
** IF CONTACTED EXIT
** Purpose is to append mask trails with Exit image
** Conditions are for any light contact	
** Unlike Walls, Exits zones can be entered
**	hence rounded up x & y are needed 
** m_y_up & m_x_up stores the previous rounded up-matrix-positions
** y & x are pixel position of m_y_up & m_x_up
*/
static void	ft_cover_exit(t_data vars, struct s_pc pc)
{
	static int	m_y_up;
	static int	m_x_up;
	int			y;
	int			x;

	y = m_y_up * vars.pc_0.hgt;
	x = m_x_up * vars.pc_0.wth;
	if (vars.matrix[pc.m_y1 / vars.pc_0.hgt][pc.m_x1 / vars.pc_0.wth] == 'E')
		vars.put_img(vars.mlx, vars.win, vars.ext0.ptr, pc.m_x1, pc.m_y1);
	else if (vars.matrix[pc.m_y1 / vars.pc_0.hgt][m_x_up] == 'E')
		vars.put_img(vars.mlx, vars.win, vars.ext0.ptr, x, pc.m_y1);
	else if (vars.matrix[m_y_up][pc.m_x1 / vars.pc_0.wth] == 'E')
		vars.put_img(vars.mlx, vars.win, vars.ext0.ptr, pc.m_x1, y);
	else if (vars.matrix[m_y_up][m_x_up] == 'E')
		vars.put_img(vars.mlx, vars.win, vars.ext0.ptr, x, y);
	m_x_up = pc.x_up;
	m_y_up = pc.y_up;
}

/*
** COVER TRAILS OF PREVIOUS POSITION
** m_x1 & m_y1:
**	Rounded down x & y coord. Always true for 1st quadrant
** m_x2 - 2nd quadrant: 
**  if pc didn't enter next left zone, no Q2, only cover Q1 and/or Q3
** m_y2 - 3rd quadrant:
**	if pc didn't enter next top zone, no Q3, only cover Q1 and/or Q2
** if m_x2 + m_y2
** 	4th quardrant is entered
*/
void	ft_cover_trails(t_data *vars, struct s_pc *pc)
{
	int	mtx_y;
	int	mtx_x;

	vars->put_img(vars->mlx, vars->win, vars->bg.ptr, pc->m_x1, pc->m_y1);
	vars->put_img(vars->mlx, vars->win, vars->bg.ptr, pc->m_x2, pc->m_y1);
	vars->put_img(vars->mlx, vars->win, vars->bg.ptr, pc->m_x1, pc->m_y2);
	vars->put_img(vars->mlx, vars->win, vars->bg.ptr, pc->m_x2, pc->m_y2);
	ft_cover_exit(*vars, *pc);
	mtx_y = pc->y / vars->pc_0.hgt;
	mtx_x = pc->x / vars->pc_0.wth;
	pc->m_x1 = mtx_x * vars->bg.wth;
	pc->m_x2 = ft_tco_int((pc->x % vars->pc_0.wth == 0), mtx_x, mtx_x + 1);
	pc->m_x2 *= vars->bg.wth;
	pc->m_y1 = mtx_y * vars->bg.hgt;
	pc->m_y2 = ft_tco_int((pc->y % vars->pc_0.hgt == 0), mtx_y, mtx_y + 1);
	pc->m_y2 *= vars->bg.hgt;
}

/*
** CONTACT COLLECTIBLES
**	Conditions are for any light contact
**	If touched any corners, remove 'C' from map
*/
void	ft_contact_collectible(t_data *vars, struct s_pc pc)
{
	int	mtx_y;
	int	mtx_x;

	mtx_y = pc.y / vars->pc_0.hgt;
	mtx_x = pc.x / vars->pc_0.wth;
	if (vars->matrix[mtx_y][mtx_x] == 'C')
		vars->matrix[mtx_y][mtx_x] = '0';
	else if (vars->matrix[mtx_y][pc.x_up] == 'C')
		vars->matrix[mtx_y][pc.x_up] = '0';
	else if (vars->matrix[pc.y_up][mtx_x] == 'C')
		vars->matrix[pc.y_up][mtx_x] = '0';
	else if (vars->matrix[pc.y_up][pc.x_up] == 'C')
		vars->matrix[pc.y_up][pc.x_up] = '0';
	else
		return ;
	vars->items--;
}
