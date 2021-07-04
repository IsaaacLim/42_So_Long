#include "so_long.h"

/*
** For Drawing
** Mimic the mlx_pixel_put but made it faster
** offset - Bytes are not aligned, hence line_length differs from window width
** color - 0x00FF0000 is hex rep of ARGB(0,255,0,0)
*/
void	my_mlx_pixel_put(t_data *vars, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * vars->line_length + x * (vars->bits_per_pixel / 8); //bbp = 32
	dst = vars->addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *vars)
{
	int x;
	int y;

	x = vars->pc.x;
	while (x < 32 + vars->pc.x)
	{
		y = vars->pc.y;
		while (y < 32 + vars->pc.y)
		{
			my_mlx_pixel_put(vars, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->pc.x, vars->pc.y); //vars->img??
}