#include "so_long.h"
#include "./GetNextLine/get_next_line.h"
#include <fcntl.h>

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
			return (0);
		}
		matrix[i] = column;
		i++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (1);
}

void ft_get_map(t_data *vars, char *file)
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
		ft_printf("Read file error(ft_map_size)\n");
	close(fd);
	vars->matrix = (char **)malloc(vars->map_hgt * (sizeof(char *) + 1));
	if (!vars->matrix)
		ft_printf("Row malloc fail\n"); //give codes
	if (!ft_fill_matrix(file, vars->matrix, vars->map_hgt))
		ft_printf("Fill matrix fail\n"); //give codes
	vars->matrix[vars->map_hgt] = NULL;
}