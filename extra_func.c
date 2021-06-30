#include "so_long.h"

void	draw_square(t_data *vars)
{
	int x;
	int y;

	x = vars->shift_x;
	while (x < 50 + vars->shift_x)
	{
		y = vars->shift_y;
		while (y < 50 + vars->shift_y)
		{
			my_mlx_pixel_put(vars, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}