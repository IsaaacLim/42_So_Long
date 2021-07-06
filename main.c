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

int	ft_enemy_1(t_data *vars)
{
	static int x;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, vars->en.x, vars->en.y);
	x += 1;
	if (x % 661 == 0)
	{
		ft_movement_en(vars, &vars->en, 1);
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
				mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, x * vars->en.wth, y * vars->en.hgt);
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

void	ft_init_mask_position(t_data *vars, struct s_img *obj)
{
	obj->mask_x1 = obj->x * vars->bg.wth;
	obj->mask_x2 = ft_ternary(vars->matrix[obj->y][obj->x + 1] != '1', (obj->x + 1 ) * vars->bg.wth, obj->mask_x1);
	obj->mask_y1 = obj->y * vars->bg.hgt;
	obj->mask_y2 = ft_ternary(vars->matrix[obj->y + 1][obj->x] != '1', (obj->y + 1 ) * vars->bg.hgt, obj->mask_y1);
}

void	ft_init_img_position(t_data *vars)
{
	vars->en.y = 2;
	vars->en.x = 1;
	vars->pc.count = 0;
	ft_init_mask_position(vars, &vars->pc);
	vars->en.mask_x1 = vars->en.x * vars->bg.wth;
	vars->en.mask_y1 = vars->en.y * vars->bg.hgt;
	vars->en.y *= vars->en.hgt;
	vars->en.x *= vars->en.wth;
	vars->en.dir = 'd';
}

int main(int argc, char **argv)
{
	t_data	vars;
	
	if (argc != 2)
	{
		ft_printf("Input a file\n");
		return (0);
	}
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))))
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
	ft_init_img_position(&vars);
	mlx_loop_hook(vars.mlx, ft_enemy_1, &vars);
	ft_control(&vars);
	mlx_loop(vars.mlx);
}