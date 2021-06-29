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

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	
	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello World!");

	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); //hex rep of ARGB(0,255,0,0)
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}