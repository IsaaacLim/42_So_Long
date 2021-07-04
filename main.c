/*
** mlx_init() - Establish connection to the correct graphical system
** mls_new_window() - Initialize a window
** mlx_loop() - Allow display to remain open
** mlx_new_image() - Initialize image in bbp (bit per pixel)
** mlx_get_data_addr() - Pass vars by reference to set data based on the current data address
*/

#include "so_long.h"

/*
** What??
*/
int		render_next_frame(t_data *vars)
{
	int y = 96;

	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->enemy, vars->test_x, y);

	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, x, y); //vars->img??
	if (vars->test_x < WIDTH - 32)
	 	vars->test_x += 0.05;
}

void	ft_background(t_data *vars)
{
	char	*img_bg = "./grass_tile.xpm";
	int		x;
	int		y;
	
	vars->background = mlx_xpm_file_to_image(vars->mlx, img_bg, &vars->img_width, &vars->img_height);
	x = 0;
	while (x <= WIDTH - vars->img_width)
	{	
		y = 0;
		while (y <= HEIGHT - vars->img_height)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x, y);
			y += vars->img_height;
		}
		x += vars->img_width;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Input a file\n");
		return (0);
	}
	t_data	vars;
	vars.shift_x = 0;
	vars.shift_y = 0;
	vars.mask_start = true;	
	vars.test_x = 0;
	
	ft_getmap(argv[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "So_Long!");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	
	char	*enemy = "images/levi.xpm";

	vars.enemy = mlx_xpm_file_to_image(vars.mlx, enemy, &vars.enemy_width, &vars.enemy_height);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);//what???
	ft_background(&vars);
	//draw_square(&vars); //img = square
	ft_control(&vars);
	
	mlx_loop(vars.mlx);
}