/*
** mlx_init() - Establish connection to the correct graphical system
** mls_new_window() - Initialize a window
** mlx_loop() - Allow display to remain open
** mlx_new_image() - Initialize image in bbp (bit per pixel)
** mlx_get_data_addr() - Pass vars by reference to set data based on the current data address
** mlx_loop_hook() - Function will be running in a loop
** mlx_xpm_file_to_image() - Init and stores the pointer to an image
** mlx_put_image_to_window() - prints the image of the specifed image pointer
*/

#include "so_long.h"

void	ft_en_move(t_data *vars, struct s_en *en)
{
	bool gameover;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->en_0.ptr, en->x, en->y);
	en->counter += 1;
	if (en->counter % en->speed == 0 && !vars->ended)
		ft_movement_en(vars, en);
	gameover = ft_contact_enemy(vars, vars->pc, *en);
	if (gameover)
		vars->ended = true;

}

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
}

void	ft_init_pc(t_data *vars, struct s_pc *obj)
{
	int y;
	int x;

	y = obj->y;
	x = obj->x;
	obj->count = 0;
	obj->x_up = x;
	obj->y_up = y;
	obj->m_x1 = x * vars->bg.wth;
	obj->m_x2 = ft_ternary(vars->matrix[y][x + 1] != '1', 
		(x + 1) * vars->bg.wth, obj->m_x1);
	obj->m_y1 = y * vars->bg.hgt;
	obj->m_y2 = ft_ternary(vars->matrix[y + 1][x] != '1', 
		(y + 1) * vars->bg.hgt, obj->m_y1);
	obj->x *= vars->pc_0.wth;
	obj->y *= vars->pc_0.hgt;
}

void	ft_free_2d_arr(char **arr)
{
	int i;

	while (arr[i])
		i++;
	while (--i >=0)
		free(arr[i]);
	free(arr);
}

void	ft_en_clone(t_data *vars, struct s_en *en, int y, int x, int count)
{
	char 	*dir;
	char	*speeds;
	char	**temp;

	dir = "wsad";
	speeds = "433,283,71,97,119,661,151,109,43,947";
	temp = ft_split(speeds, ',');
	en->rank = count;
	en->y = y * vars->en_0.hgt;
	en->x = x * vars->en_0.wth;
	en->m_y1 = y * vars->bg.hgt;
	en->m_x1 = x * vars->bg.wth;
	en->dir = dir[count % 4];
	en->counter = 1;
	en->speed = ft_atoi(temp[count - 1]);
	ft_free_2d_arr(temp);
}

void	ft_init_enemy(t_data *vars, int y, int x)
{
	static int count;

	count++;
	if (count > NUM_OF_ENEMIES)
		return;
	else if (count == 1)
		ft_en_clone(vars, &vars->en1, y, x, count);
	else if (count == 2)
		ft_en_clone(vars, &vars->en2, y, x, count);
	else if (count == 3)
		ft_en_clone(vars, &vars->en3, y, x, count);
	else if (count == 4)
		ft_en_clone(vars, &vars->en4, y, x, count);
	else if (count == 5)
		ft_en_clone(vars, &vars->en5, y, x, count);
	else if (count == 6)
		ft_en_clone(vars, &vars->en6, y, x, count);
	else if (count == 7)
		ft_en_clone(vars, &vars->en7, y, x, count);
	else if (count == 8)
		ft_en_clone(vars, &vars->en8, y, x, count);
	else if (count == 9)
		ft_en_clone(vars, &vars->en9, y, x, count);
	else if (count == 10)
		ft_en_clone(vars, &vars->en10, y, x, count);
}

void	ft_background(t_data *vars)
{
	int	x;
	int	y;
	int	e;
	
	e = 0;
	y = -1;
	while (++y < vars->map_hgt)
	{	
		x = -1;
		while (++x < vars->map_wth)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, x * vars->bg.wth, y * vars->bg.hgt);
			if (vars->matrix[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wl.ptr, x * vars->wl.wth, y * vars->wl.hgt);
			else if (vars->matrix[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->clt.ptr, x * vars->clt.wth, y * vars->clt.hgt);
			else if (vars->matrix[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->ext.ptr, x * vars->ext.wth, y * vars->ext.hgt);
			else if (vars->matrix[y][x] == '0' && e % ENEMY_POSITION == 0)
				ft_init_enemy(vars, y, x);
			e++;
		}
	}
}

void	ft_xpm_file_to_image(t_data *vars)
{
	char	*bg = "images/grass_tile.xpm";
	char	*pc_0 = "images/yoshi_f1.xpm";
	char	*pc_r1 = "images/yoshi_r1.xpm";
	char	*en_0 = "images/levi.xpm";
	char	*wl = "images/rock.xpm";
	char	*ext = "images/dome.xpm";
	char	*clt = "images/flower.xpm";

	vars->bg.ptr = mlx_xpm_file_to_image(vars->mlx, bg, &vars->bg.wth, &vars->bg.hgt);
	vars->pc_0.ptr = mlx_xpm_file_to_image(vars->mlx, pc_0, &vars->pc_0.wth, &vars->pc_0.hgt);
	vars->pc_r1.ptr = mlx_xpm_file_to_image(vars->mlx, pc_r1, &vars->pc_r1.wth, &vars->pc_r1.hgt);
	vars->en_0.ptr = mlx_xpm_file_to_image(vars->mlx, en_0, &vars->en_0.wth, &vars->en_0.hgt);
	vars->wl.ptr = mlx_xpm_file_to_image(vars->mlx, wl, &vars->wl.wth, &vars->wl.hgt);
	vars->ext.ptr = mlx_xpm_file_to_image(vars->mlx, ext, &vars->ext.wth, &vars->ext.hgt);
	vars->clt.ptr = mlx_xpm_file_to_image(vars->mlx, clt, &vars->clt.wth, &vars->clt.hgt);
}

int main(int argc, char **argv)
{
	t_data	vars;
	
	if (argc != 2)
	{
		ft_printf("Input a file\n");
		return (0);
	}
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))) //.bergur
		ft_error("Input '.ber' file", 0, &vars);
	ft_get_map(&vars, argv[1]);
	vars.mlx = mlx_init();
	ft_xpm_file_to_image(&vars);
	vars.win_wth = vars.map_wth * vars.bg.wth;
	vars.win_hgt = vars.map_hgt * vars.bg.hgt;
	vars.win = mlx_new_window(vars.mlx, vars.win_wth, vars.win_hgt, "So_Long!");
	vars.img = mlx_new_image(vars.mlx, vars.win_wth, vars.win_hgt);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	vars.ended = false;
	ft_background(&vars);
	ft_init_pc(&vars, &vars.pc);
	mlx_loop_hook(vars.mlx, ft_en_loop, &vars);
	ft_control(&vars);
	mlx_loop(vars.mlx);
}