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

void	ft_cover_trails(t_data *vars, int keycode)
{
	/*
	if (vars->mask_start)
	{
		vars->mask_x = 0; // get this to be player start pos
		vars->mask_y = 0;
		vars->mask_start = false;
	}

	printf(" x: %d, y: %d\n", vars->mask_x, vars->mask_y);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, vars->mask_x, vars->mask_y);

	//New position if x_right
	if (keycode == 100) //d
		vars->mask_x = vars->shift_x / vars->img_width * vars->img_width; //leftside
	//New position if x_left
	else if (keycode == 97) //a
	{
		if (vars->shift_x % vars->img_width == 0)
			vars->mask_x = vars->shift_x / vars->img_width * vars->img_width;
		else
			vars->mask_x = (vars->shift_x / vars->img_width + 1) * vars->img_width;
	}
	vars->mask_y = vars->shift_y / vars->img_height * vars->img_height;
	*/
	int start_postition;
	start_postition = 0; // get this to be player start pos
	if (vars->mask_start)
	{
		vars->mask_x1 = start_postition * vars->img_width;
		vars->mask_x2 = (start_postition + 1) * vars->img_width;
		vars->mask_y1 = start_postition * vars->img_height;
		vars->mask_y2 = (start_postition + 1) * vars->img_height;
		vars->mask_start = false;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, vars->mask_x1, vars->mask_y1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, vars->mask_x2, vars->mask_y1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, vars->mask_x1, vars->mask_y2);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background, vars->mask_x2, vars->mask_y2);
	vars->mask_x1 = vars->shift_x / vars->img_width * vars->img_width;
	vars->mask_x2 = (vars->shift_x / vars->img_width + 1 ) * vars->img_width;
	vars->mask_y1 = vars->shift_y / vars->img_height * vars->img_height;
	vars->mask_y2 = (vars->shift_y / vars->img_height + 1) * vars->img_height;
	printf(" x1: %d, x2: %d\n", vars->mask_x1, vars->mask_x2);

}
void	ft_character(t_data *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player, vars->shift_x, vars->shift_y);
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
		vars->shift_y -= 8;
	if (keycode == 97) //a
		vars->shift_x -= 8;
	if (keycode == 115) //s
		vars->shift_y += 8;
	if (keycode == 100) //d
		vars->shift_x += 8;
	printf("\tkey: %c shift_x: %d shift_y: %d", keycode, vars->shift_x, vars->shift_y);
	//mlx_clear_window(vars->mlx, vars->win);
	//ft_background(vars);
	ft_cover_trails(vars, keycode);
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