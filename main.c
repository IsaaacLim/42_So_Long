/*
** mlx_init() - Establish connection to the correct graphical system
** mls_new_window() - Initialize a window
** mlx_loop() - Allow display to remain open
** mlx_new_image() - Initialize image in bbp (bit per pixel)
** mlx_get_data_addr() - Pass vars by reference to set data based on the current data address
*/

#include "so_long.h"

/*
** Mimic the mlx_pixel_put but made it faster
** offset - Bytes are not aligned, hence line_length differs from window width
** color - 0x00FF0000 is hex rep of ARGB(0,255,0,0)
*/
void	my_mlx_pixel_put (t_data *vars, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * vars->line_length + x * (vars->bits_per_pixel / 8);
	dst = vars->addr + offset;
	*(unsigned int *)dst = color;
}

/*
** Hooking intercepts functions calls, messages ot events
*/
int		key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook!\n");
}

/*
** Keypress will close window
*/
/* SEG FAULT with mlx_xpm_file_to_image
int		close(int keycode, t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
}*/

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

int main(void)
{
	// t_vars	vars;
	t_data	vars;
	char	*img_m = "./test96.xpm";
	
	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello World!");

	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);

	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
		 &vars.endian);

	my_mlx_pixel_put(&vars, 10, 10, 0x00FF0000); //bring2front by having this and mlx_get_data_addr after img
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	for(int i = 200; i <= 400; i++)
	{
		my_mlx_pixel_put(&vars, i, i, 0x00FF0000); //hex rep of ARGB(0,255,0,0)
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	}

	 mlx_key_hook(vars.win, key_hook, &vars); //Key press will call key_hook()
	// mlx_hook(vars.win, 04, 1L<<2, close, &vars); //event, mask (not sure how to use it yet)

	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);//what???

	vars.img = mlx_xpm_file_to_image(vars.mlx, img_m, &vars.img_width, &vars.img_height);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	
	
	
	mlx_loop(vars.mlx);
}