#include "so_long.h"
#include "./GetNextLine/get_next_line.h"
#include <fcntl.h>

static void ft_verify_map(t_data *vars, int i, int j)
{
	bool has_exit;
	bool has_collectible;
	bool has_start_pos;
	int x;
	int y;

	x = 0;
	while (x < i)
	{
		y = 0;
		while (y < j)
		{
			if (x == 0 || x == i - 1 || y == 0 || y == j - 1)
			{
				if (vars->matrix[x][y] != '1')
					ft_error("Map not surrounded by walls", 1, vars);
			}
			else if (!(ft_strchr("01CEP", vars->matrix[x][y])))
				ft_error("Map contains invalid character", 1, vars);
			if (vars->matrix[x][y] == 'E')
				has_exit = true;
			if (vars->matrix[x][y] == 'C')
				has_collectible = true;
			if (vars->matrix[x][y] == 'P')
				has_start_pos = true;
			y++;
		}
		x++;
	}
	if (!(has_exit && has_collectible && has_start_pos))
		ft_error("Missing Exit/Collectible/Starting position", 1, vars);
	if (x == y)
		ft_error("Map is square", 1, vars);
}

static void ft_display_map(t_data *vars)
{
	int i;
	int j;

	i = 0;
	ft_printf("Map:\n");
	while (i < vars->map_hgt)
	{
		j = 0;
		while (vars->matrix[i][j])
		{
			ft_printf("%c", vars->matrix[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	ft_verify_map(vars, i, j);
}

static int	ft_fill_matrix(char *file, char **matrix, int height)
{
	char	*line;	
	char	*column;
	int 	fd;
	int 	ret;
	int		i;

	fd = open(file, O_RDONLY);
	ret = get_next_line(fd, &line);
	i = 0;
	while (ret > 0)
	{
		column = ft_strdup(line);
		if (!column)
		{
			ft_free_matrix(matrix, i);
			return (-1);
		}
		matrix[i] = column;
		i++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	if (ret == -1)
		return (-1);
	close(fd);
	return (1);
}

void	ft_get_map(t_data *vars, char *file)
{
	char 	*line;
	int 	fd;
	int 	ret;

	vars->map_hgt = 0;
	fd = open(file, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		vars->map_hgt++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	if (ret == -1)
		ft_error("Read file error", 0, vars);
	close(fd);
	vars->matrix = (char **)malloc(vars->map_hgt * (sizeof(char *) + 1));
	if (!vars->matrix)
		ft_error("Matrix malloc error", 0, vars);
	if (!(ft_fill_matrix(file, vars->matrix, vars->map_hgt)))
		ft_error("Matrix fill error", 0, vars);
	vars->matrix[vars->map_hgt] = NULL;
	ft_display_map(vars);
}