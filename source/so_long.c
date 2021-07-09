#include "so_long.h"

/*
** mlx_init() - Establish connection to the correct graphical system
** mls_new_window() - Initialize a window
** mlx_loop() - Allow display to remain open
** mlx_new_image() - Initialize image in bbp (bit per pixel)
** mlx_get_data_addr() - Pass vars by reference to set data
**	based on the current data address
** mlx_loop_hook() - Function will be running in a loop.
**	May intercept function calls, messages or events
** mlx_xpm_file_to_image() - Init and stores the pointer to an image
** mlx_put_image_to_window() - prints the image of the specifed image pointer
*/

/*
** Shorten mlx function names
*/
void	ft_store_mlx_function(t_data *vars)
{
	vars->put_img = mlx_put_image_to_window;
	vars->xpm_img = mlx_xpm_file_to_image;
}

/*
** Functions that are constantly looped by mlx_loop_hook
*/
int	ft_loops(t_data *vars)
{
	ft_put_steps(*vars);
	ft_en_loop(vars);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	vars;

	if (argc != 2)
		ft_error(&vars, "Input a file", false);
	ft_parse_map(&vars, argv[1]);
	ft_store_mlx_function(&vars);
	vars.mlx = mlx_init();
	ft_xpm_img(&vars);
	ft_init_vars(&vars);
	vars.win = mlx_new_window(vars.mlx, vars.win_wth, vars.win_hgt, "So_Long!");
	vars.img = mlx_new_image(vars.mlx, vars.win_wth, vars.win_hgt);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bbp, &vars.len, &vars.endian);
	ft_map_img(&vars);
	ft_control_hook(&vars);
	mlx_loop_hook(vars.mlx, ft_loops, &vars);
	mlx_loop(vars.mlx);
}
