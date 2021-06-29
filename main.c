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
*/
void	my_mlx_pixel_put (t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

/*
** Hooking intercepts functions calls, messages ot events
*/
int		key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
}

int main(void)
{
	t_vars	vars;
	t_data	img;
	
	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello World!");

	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		 &img.endian);

	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); //hex rep of ARGB(0,255,0,0)
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	for(int i = 200; i <= 400; i++)
	{
		my_mlx_pixel_put(&img, i, i, 0x00FF0000); //hex rep of ARGB(0,255,0,0)
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	}

	mlx_key_hook(vars.win, key_hook, &vars); //Key press will call key_hook()
	mlx_loop(vars.mlx);
}