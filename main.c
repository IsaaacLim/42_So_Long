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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->en.ptr, vars->en.X, vars->en.Y);
	if (vars->en.X < WIDTH - 32)
	 	vars->en.X += 0.05;
}

void	ft_background(t_data *vars)
{
	int		x;
	int		y;
	
	x = 0;
	while (x <= WIDTH - vars->bg.wth)
	{	
		y = 0;
		while (y <= HEIGHT - vars->bg.hgt)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->bg.ptr, x, y);
			y += vars->bg.hgt;
		}
		x += vars->bg.wth;
	}
}

void	ft_xpm_file_to_image(t_data *vars)
{
	char	*bg = "images/grass_tile.xpm";
	char	*pc = "images/player.xpm";
	char	*en = "images/levi.xpm";

	vars->bg.ptr = mlx_xpm_file_to_image(vars->mlx, bg, &vars->bg.wth, &vars->bg.hgt);
	vars->pc.ptr = mlx_xpm_file_to_image(vars->mlx, pc, &vars->pc.wth, &vars->pc.hgt);
	vars->en.ptr = mlx_xpm_file_to_image(vars->mlx, en, &vars->en.wth, &vars->en.hgt);

}

void	ft_init_img_position(t_data *vars)
{
	vars->pc.x = 0;
	vars->pc.y = 0;
	vars->en.X = 0;
	vars->en.Y = 96;
	vars->bg.x = vars->pc.x * vars->bg.wth;
	vars->bg.x2 = (vars->pc.x + 1) * vars->bg.wth;
	vars->bg.y = vars->pc.y * vars->bg.hgt;
	vars->bg.y2 = (vars->pc.y + 1) * vars->bg.hgt;
}

int main(int argc, char **argv)
{
	t_data	vars;
	
	if (argc != 2)
	{
		printf("Input a file\n");
		return (0);
	}
	ft_get_map(&vars, argv[1]);



	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "So_Long!");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	ft_xpm_file_to_image(&vars);
	ft_background(&vars);
	ft_init_img_position(&vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	//draw_square(&vars); //img = square
	ft_control(&vars);
	
	mlx_loop(vars.mlx);
}