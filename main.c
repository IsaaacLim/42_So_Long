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

int		render_next_frame(t_data *vars)
{
	bool	end;
	if (vars->en.x < vars->win_wth - vars->en.wth)
		vars->en.X += 0.005;
	else
		end = true;
	if ((int)vars->en.X % 8 == 0 && !end)
	{
		vars->en.x = (int)vars->en.X;
		ft_cover_trails(vars, &vars->en);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, vars->en.x, vars->en.y);
	}
}

void	ft_background(t_data *vars)
{
	int		x;
	int		y;
	
	y = 0;
	while (y < vars->map_hgt)
	{	
		x = 0;
		while (x < vars->map_wth)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, x * vars->bg.wth, y * vars->bg.hgt);
			if (vars->matrix[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wl.ptr, x * vars->wl.wth, y * vars->wl.hgt);
			// else
			x++;
		}
		y++;
	}
}

void	ft_xpm_file_to_image(t_data *vars)
{
	char	*bg = "images/grass_tile.xpm";
	char	*pc = "images/player.xpm";
	char	*en = "images/levi.xpm";
	char	*wl = "images/rock.xpm";

	vars->bg.ptr = mlx_xpm_file_to_image(vars->mlx, bg, &vars->bg.wth, &vars->bg.hgt);
	vars->pc.ptr = mlx_xpm_file_to_image(vars->mlx, pc, &vars->pc.wth, &vars->pc.hgt);
	vars->en.ptr = mlx_xpm_file_to_image(vars->mlx, en, &vars->en.wth, &vars->en.hgt);
	vars->wl.ptr = mlx_xpm_file_to_image(vars->mlx, wl, &vars->wl.wth, &vars->wl.hgt);
}

void	ft_init_mask_position(t_data *vars, struct s_img *chr)
{
	chr->mask_x1 = chr->x * vars->bg.wth;
	chr->mask_x2 = (chr->x + 1) * vars->bg.wth;
	chr->mask_y1 = chr->y * vars->bg.hgt;
	chr->mask_y2 = (chr->y + 1) * vars->bg.hgt;
}

void	ft_init_img_position(t_data *vars)
{
	vars->en.x = 0;
	vars->en.y = 96;
	vars->en.X = vars->en.x;
	vars->en.Y = vars->en.y;
	ft_init_mask_position(vars, &vars->en);
	ft_init_mask_position(vars, &vars->pc);
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
	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	ft_control(&vars);
	mlx_loop(vars.mlx);
}