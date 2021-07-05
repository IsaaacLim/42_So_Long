#include "so_long.h"

void	ft_free_matrix(char **matrix, int height)
{
	while (--height >= 0)
	{
		ft_bzero(matrix[height], ft_strlen(matrix[height]));
		free(matrix[height]);
	}
	free(matrix);
}

void	ft_close_window(t_data *vars)
{
	ft_printf("\n");
	ft_free_matrix(vars->matrix, vars->map_hgt);
	mlx_destroy_image(vars->mlx, vars->en.ptr);
	mlx_destroy_image(vars->mlx, vars->pc.ptr);
	mlx_destroy_image(vars->mlx, vars->bg.ptr);
	mlx_destroy_image(vars->mlx, vars->wl.ptr);
	mlx_destroy_image(vars->mlx, vars->ext.ptr);
	mlx_destroy_image(vars->mlx, vars->clt.ptr);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}

void	ft_error(char *code, int i, t_data *vars)
{
	ft_printf("Error\n");
	ft_printf("%s\n", code);
	if (i == 1)
		ft_free_matrix(vars->matrix, vars->map_hgt);
	exit (0);
	
}