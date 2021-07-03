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

/*
** Keypress will close window
*/
void	ft_close_window(t_data *vars)
{
	printf("\n");
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_image(vars->mlx, vars->player);
	mlx_destroy_image(vars->mlx, vars->background);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}

void	ft_cover_trails(t_data *vars)
{
	/*
	char	*img_bg = "./grass_tile.xpm";
	int		x = vars->shift_x;
	int		y = vars->shift_y;

	vars->background = mlx_xpm_file_to_image(vars->mlx, img_bg, &vars->img_width, &vars->img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x, y);
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x - 32, y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x + 32, y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x, y - 32);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, x, y + 32);
	*/
}
void	ft_character(t_data *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player, vars->shift_x, vars->shift_y);
	//ft_cover_trails(vars);
}
/*
** Hooking intercepts functions calls, messages ot events
** keycode follows ASCII [prtinf("%d", keycode) for more]
*/
int		ft_wasd(int keycode, t_data *vars)
{
	printf("key_hook: %d", keycode);
	if (keycode == 65307)
		ft_close_window(vars);
	if (keycode == 119) //w
		vars->shift_y -= 10;
	if (keycode == 97) //a
		vars->shift_x -= 10;
	if (keycode == 115) //s
		vars->shift_y += 10;
	if (keycode == 100) //d
		vars->shift_x += 10;
	printf("\tkey: %c shift_x: %d shift_y: %d\n", keycode, vars->shift_x, vars->shift_y);
	//mlx_clear_window(vars->mlx, vars->win);
	//ft_background(vars);
	ft_character(vars);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->shift_x, vars->shift_y);
	return (0);
}

int		ft_mouse(int button, int x, int y, t_data *vars)
{
	// int x;
	// int y;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	printf("pos:%d %d %d \n", button, x, y);
	//if (button == 1 && (x >= 593 && x <= 640) && (y >= -30 && y <= 0))
	if (button == 1 && (x >= 593 && x <= 640) && (y >= 20 && y <= 40))
		ft_close_window(vars);
	return (0);
}

int		ft_control(t_data *vars)
{
	char	*player = "./player.xpm";

	vars->player = mlx_xpm_file_to_image(vars->mlx, player, &vars->player_width, &vars->player_height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player, vars->shift_x, vars->shift_y);

	// draw_square(vars);
	mlx_key_hook(vars->win, ft_wasd, vars); //Key press will call key_hook()
	mlx_mouse_hook(vars->win, ft_mouse, vars);
}