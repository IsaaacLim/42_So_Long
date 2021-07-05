#include "so_long.h"
#include "./GetNextLine/get_next_line.h"
#include <fcntl.h>

static void ft_verify_map(t_data *vars, int i, int j)
{
	bool has_exit;
	int x;
	int y;

	vars->pc.x = 0;
	vars->items = 0;
	y = 0;
	while (y < i)
	{
		x = 0;
		while (x < j)
		{
			if (y == 0 || y == i - 1 || x == 0 || x == j - 1)
			{
				if (vars->matrix[y][x] != '1')
					ft_error("Map not surrounded by walls", 1, vars);
			}
			else if (!(ft_strchr("01CEP", vars->matrix[y][x])))
				ft_error("Map contains invalid character", 1, vars);
			if (vars->matrix[y][x] == 'E')
				has_exit = true;
			if (vars->matrix[y][x] == 'C')
				vars->items++;
			if (vars->matrix[y][x] == 'P')
			{
				vars->pc.y = y;
				vars->pc.x = x;
			}
			x++;
		}
		y++;
	}
	if (!(has_exit && vars->items > 0 && vars->pc.y > 0))
		ft_error("Missing Exit/Collectible/Starting position", 1, vars);
	if (y == x)
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
	vars->map_wth = j;
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