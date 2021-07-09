
// mlx_init() - Establish connection to the correct graphical system
// mls_new_window() - Initialize a window
// mlx_loop() - Allow display to remain open
// mlx_new_image() - Initialize image in bbp (bit per pixel)
// mlx_get_data_addr() - Pass vars by reference to set data based on the current data address
// mlx_loop_hook() - Function will be running in a loop
// mlx_xpm_file_to_image() - Init and stores the pointer to an image
// mlx_put_image_to_window() - prints the image of the specifed image pointer

#include "so_long.h"

void	ft_create_collectibles(t_data vars, int y, int x)
{
	static int count;
	int pos_x;
	int pos_y;
	
	pos_x = x * vars.clt_0.wth;
	pos_y = y * vars.clt_0.hgt;
	if (count % 3 == 1)
		vars.put_img(vars.mlx, vars.win, vars.clt_0.ptr, pos_x, pos_y);
	else if (count % 3 == 2)
		vars.put_img(vars.mlx, vars.win, vars.clt_l.ptr, pos_x, pos_y);
	else
		vars.put_img(vars.mlx, vars.win, vars.clt_r.ptr, pos_x, pos_y);
	count++;
}

void	ft_map_img(t_data *vars)
{
	int	y;
	int	x;
	int	e;
	
	e = 0;
	y = -1;
	while (++y < vars->map_hgt)
	{	
		x = -1;
		while (++x < vars->map_wth)
		{
			vars->put_img(vars->mlx, vars->win, vars->bg.ptr, x * vars->bg.wth, y * vars->bg.hgt);
			if (vars->matrix[y][x] == '1')
				vars->put_img(vars->mlx, vars->win, vars->wl.ptr, x * vars->wl.wth, y * vars->wl.hgt);
			else if (vars->matrix[y][x] == 'C')
				ft_create_collectibles(*vars, y, x);
			else if (vars->matrix[y][x] == 'E')
				vars->put_img(vars->mlx, vars->win, vars->ext0.ptr, x * vars->ext0.wth, y * vars->ext0.hgt);
			else if (vars->matrix[y][x] == '0' && e % ENEMY_POSITION == 0)
				ft_create_enemy(vars, y, x);
			e++;
		}
	}
}

void	ft_store_mlx_function(t_data *vars)
{
	vars->put_img = mlx_put_image_to_window;
	vars->xpm_img = mlx_xpm_file_to_image;
}

void	ft_put_steps(t_data vars)
{
	char	steps[12];
	char	*temp;
	int		i;
	int		j;

	j = ft_strlcpy(steps, "STEPS: 00000", 12);
	temp = ft_lltoa(vars.pc.move_count);
	i = 0;
	while (temp[i])
		i++;
	steps[j - 1] = temp[i - 1];
	while (--i >= 0)
		steps[--j] = temp[i];
	free(temp);
	vars.put_img(vars.mlx, vars.win, vars.sc.ptr, 8, 4);
	mlx_string_put(vars.mlx, vars.win, 16, 22, 0x006f235f, steps);
}

int ft_loops(t_data *vars)
{
	ft_put_steps(*vars);
	ft_en_loop(vars);
	return (1);
}
	

int main(int argc, char **argv)
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
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	ft_map_img(&vars);
	ft_control_hook(&vars);
	mlx_loop_hook(vars.mlx, ft_loops, &vars);
	mlx_loop(vars.mlx);
}