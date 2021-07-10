#include "so_long.h"

/*
** EXIT.c
** Contains the functions that has to be executed upon program termination
** Either on purpose or by any error
*/

/*
** Used to free map data stored in a matrix
*/
void	ft_free_matrix(char **matrix, int height)
{
	while (--height >= 0)
	{
		ft_bzero(matrix[height], ft_strlen(matrix[height]));
		free(matrix[height]);
	}
	free(matrix);
}

/*
** Print specific error messages that are passed & exit program
** Used only during initial phase of reading map
*/
void	ft_error( t_data *vars, char *code, bool has_matrix)
{
	ft_printf("Error\n");
	ft_printf("%s\n", code);
	if (has_matrix)
		ft_free_matrix(vars->matrix, vars->map_hgt);
	exit (0);
}

/*
** Final function in the program
** Ran upon termination
*/
int	ft_close_window(t_data *vars)
{
	ft_free_matrix(vars->matrix, vars->map_hgt);
	mlx_destroy_image(vars->mlx, vars->bg.ptr);
	mlx_destroy_image(vars->mlx, vars->wl.ptr);
	mlx_destroy_image(vars->mlx, vars->clt_0.ptr);
	mlx_destroy_image(vars->mlx, vars->clt_l.ptr);
	mlx_destroy_image(vars->mlx, vars->clt_r.ptr);
	mlx_destroy_image(vars->mlx, vars->ext0.ptr);
	mlx_destroy_image(vars->mlx, vars->ext1.ptr);
	mlx_destroy_image(vars->mlx, vars->en_0.ptr);
	mlx_destroy_image(vars->mlx, vars->en_1.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_0.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_w1.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_w2.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_s1.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_s2.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_a1.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_a2.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_d1.ptr);
	mlx_destroy_image(vars->mlx, vars->pc_d2.ptr);
	mlx_destroy_image(vars->mlx, vars->sc.ptr);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit (0);
}
