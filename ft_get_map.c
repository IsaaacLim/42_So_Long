#include "so_long.h"
#include "./GetNextLine/get_next_line.h"
#include <fcntl.h>

static void	ft_fill_matrix(char *file, char **matrix, int height)
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
			ft_error("Matrix fill error");
		}
		matrix[i] = column;
		i++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	if (ret == -1)
		ft_error("Read file error");
	close(fd);
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
		ft_error("Read file error");
	close(fd);
	vars->matrix = (char **)malloc(vars->map_hgt * (sizeof(char *) + 1));
	if (!vars->matrix)
		ft_error("Matrix malloc error");
	ft_fill_matrix(file, vars->matrix, vars->map_hgt);
	vars->matrix[vars->map_hgt] = NULL;
}