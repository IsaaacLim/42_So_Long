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

void	ft_en_move(t_data *vars, struct s_img *en)
{
	bool gameover;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, en->x, en->y);
	en->counter += 1;
	if (en->counter % en->speed == 0 && !vars->ended)
		ft_movement_en(vars, en);
	gameover = ft_contact_enemy(vars, vars->pc, *en);
	if (gameover)
		vars->ended = true;

}

int	ft_en_loop(t_data *vars)
{
	ft_en_move(vars, &vars->en);
	ft_en_move(vars, &vars->en2);
	// bool gameover;
	// static int x;

	// mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, vars->en.x, vars->en.y);
	// x += 1;
	// if (x % vars->en.speed == 0 && !vars->ended)
	// 	ft_movement_en(vars, &vars->en);
	// gameover = ft_contact_enemy(vars, vars->pc, vars->en);
	// if (gameover)
	// 	vars->ended = true;
}

void	ft_init_pc(t_data *vars)
{
	int y;
	int x;

	y = vars->pc.y;
	x = vars->pc.x;
	vars->pc.count = 0;
	vars->pc.x_up = x;
	vars->pc.y_up = y;
	vars->pc.mask_x1 = x * vars->bg.wth;
	vars->pc.mask_x2 = ft_ternary(vars->matrix[y][x + 1] != '1', 
		(x + 1) * vars->bg.wth, vars->pc.mask_x1);
	vars->pc.mask_y1 = y * vars->bg.hgt;
	vars->pc.mask_y2 = ft_ternary(vars->matrix[y + 1][x] != '1', 
		(y + 1) * vars->bg.hgt, vars->pc.mask_y1);
}

void	ft_en_clone(t_data *vars, struct s_img *en, int y, int x, char c)
{
	en->y = y * vars->en.hgt;
	en->x = x * vars->en.wth;
	en->mask_y1 = y * vars->bg.hgt;
	en->mask_x1 = x * vars->bg.wth;
	en->dir = c;
	en->counter = 1;
}

void	ft_init_enemy(t_data *vars, int y, int x)
{
	static int count;

	count++;
	ft_printf("enemy count: %d\n", count);
	if (count > 2)
		return ;
	if (count == 2)
	{
		ft_en_clone(vars, &vars->en, y, x, 'd');
		vars->en.rank = count;
		vars->en.speed = 661;
	}
	if (count == 1)
	{
		ft_en_clone(vars, &vars->en2, y, x, 'd');
		vars->en2.rank = count;
		vars->en2.speed = 661;
		ft_printf("clone 2\n");
	}
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
			else if (e % 50 == 0)
				ft_init_enemy(vars, y, x);
				// mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, x * vars->en.wth, y * vars->en.hgt);
			e++;
		}
	}
}

void	ft_xpm_file_to_image(t_data *vars)
{
	char	*bg = "images/grass_tile.xpm";
	char	*pc = "images/player.xpm";
	char	*en = "images/levi.xpm";
	char	*wl = "images/rock.xpm";
	char	*ext = "images/dome.xpm";
	char	*clt = "images/flower.xpm";

	vars->bg.ptr = mlx_xpm_file_to_image(vars->mlx, bg, &vars->bg.wth, &vars->bg.hgt);
	vars->pc.ptr = mlx_xpm_file_to_image(vars->mlx, pc, &vars->pc.wth, &vars->pc.hgt);
	vars->en.ptr = mlx_xpm_file_to_image(vars->mlx, en, &vars->en.wth, &vars->en.hgt);
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
	ft_background(&vars);
	ft_init_pc(&vars);
	mlx_loop_hook(vars.mlx, ft_en_loop, &vars);
	ft_control(&vars);
	if (vars.ended)
		ft_printf("GAME OVER\n");
	mlx_loop(vars.mlx);
}