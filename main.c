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
	int	x;
	int y;

	x = 100;
	y = 200;
	x++;
	y++;
	my_mlx_pixel_put(vars, x, y, 0x0000FF00);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void	ft_background(t_data *vars)
{
	char	*img_bg = "./grass_tile.xpm";
	int		x;
	int		y;
	
	//vars->img = mlx_xpm_file_to_image(vars->mlx, img_bg, &vars->img_width, &vars->img_height);
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
/*
int close (int keycode, t_data *vars)
{
	ft_close_window(vars);
	exit (0);
}
*/
int main(void)
{
	t_data	vars;
	vars.shift_x = 0;
	vars.shift_y = 0;
	vars.mask_start = true;	
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "So_Long!");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	
	// mlx_hook(vars.win, 04, 1L<<2, close, &vars); //event, mask (not sure how to use it yet)

	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);//what???
	ft_background(&vars);
	//draw_square(&vars); //img = square
	ft_control(&vars);
	//mlx_hook(vars.win, 17, 1L<<8, close, &vars); //SEG FAULT
	
	mlx_loop(vars.mlx);
}