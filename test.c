#include "so_long.h"

void	my_mlx_pixel_put (t_data *vars, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * vars->line_length + x * (vars->bits_per_pixel / 8);
	dst = vars->addr + offset;
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_data	vars;
	char	*img_s = "./test20.xpm";
	char	*img_m = "./test96.xpm";

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello World!");
	
	vars.img = mlx_new_image(vars.mlx, 640, 480);
	//vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	//my_mlx_pixel_put(&vars, 5, 5, 0x00FF0000);

	//vars.img = mlx_xpm_file_to_image(vars.mlx, img_m, &vars.img_width, &vars.img_height);
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	
	vars.img = mlx_xpm_file_to_image(vars.mlx, img_s, &vars.img_width, &vars.img_height);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	my_mlx_pixel_put(&vars, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	

	mlx_loop(vars.mlx);
}