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
	printf("\n");
	ft_free_matrix(vars->matrix, vars->map_hgt);
	mlx_destroy_image(vars->mlx, vars->en.ptr);
	mlx_destroy_image(vars->mlx, vars->pc.ptr);
	mlx_destroy_image(vars->mlx, vars->bg.ptr);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}

void	ft_error(char *code)
{
	if (ft_strncmp("Read file error", code, ft_strlen(code)) == 0)
		ft_printf("%s\n", code);
	else if (ft_strncmp("Matrix malloc error", code, ft_strlen(code)) == 0)
		ft_printf("%s\n", code);
	else if (ft_strncmp("Matrix fill error", code, ft_strlen(code)) == 0)
		ft_printf("%s\n", code);
	exit (0);
}