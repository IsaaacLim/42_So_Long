#include "so_long.h"
#include "../Libft/includes/get_next_line.h"
#include <fcntl.h>

/*
** Helper function for ft_verify_map();
*/
static void	ft_check(t_data *vars, int y, int x, bool *has_exit)
{
	if (y == 0 || y == vars->map_hgt - 1 || x == 0 || x == vars->map_wth - 1)
	{
		if (vars->matrix[y][x] != '1')
			ft_error(vars, "Map not surrounded by walls", true);
	}
	else if (!(ft_strchr("01CEP", vars->matrix[y][x])))
		ft_error(vars, "Map contains invalid character", true);
	if (vars->matrix[y][x] == 'E')
		*has_exit = true;
	if (vars->matrix[y][x] == 'C')
		vars->items++;
	if (vars->matrix[y][x] == 'P')
	{
		vars->pc.y = y;
		vars->pc.x = x;
	}
}

/*
** Verify doesn't use while (y < hgt) & (x < wth)
**	to check for variable width between each line of matrix
** Function also:
**	- Stores the starting position of the player
**	- Number of collectibles present
*/
static void	ft_verify_map(t_data *vars)
{
	bool	has_exit;
	int		x;
	int		y;

	vars->pc.x = 0;
	vars->items = 0;
	y = -1;
	while (vars->matrix[++y])
	{
		x = -1;
		while (vars->matrix[y][++x])
			ft_check(vars, y, x, &has_exit);
		if (x != vars->map_wth)
			ft_error(vars, "Map length is inconsistent", true);
	}
	if (!(has_exit && vars->items > 0 && vars->pc.y > 0))
		ft_error(vars, "Missing Exit/Collectible/Starting position", true);
	if (y == x)
		ft_error(vars, "Map is square", true);
}

/*
** Fill matrix of created 2D array
*/
static int	ft_fill_matrix(char *file, char **matrix)
{
	char	*line;	
	char	*column;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
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
	}
	free(line);
	if (get_next_line(fd, &line) == -1)
		return (-1);
	free(line);
	close(fd);
	return (1);
}

/*
** Read file & create 2D array (matrix)
*/
static void	ft_get_map(t_data *vars, char *file)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(file, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		vars->map_hgt++;
		vars->map_wth = ft_strlen(line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	if (ret == -1)
		ft_error(vars, "Read file error", false);
	close(fd);
	vars->matrix = (char **)malloc(vars->map_hgt * (sizeof(char *) + 1));
	if (!vars->matrix)
		ft_error(vars, "Matrix malloc error", false);
	if (!(ft_fill_matrix(file, vars->matrix)))
		ft_error(vars, "Matrix fill error", false);
	vars->matrix[vars->map_hgt] = NULL;
}

/*
** If argc == 2,
** 1. Check map is .ber extension
** 2. Read file and store map into a matrix
** 3. Display map on screen
** 4. Verify if map is valid
*/
void	ft_parse_map(t_data *vars, char *file)
{
	char	temp[4];
	int		len;
	int		i;
	int		y;
	int		x;

	len = ft_strlen(file);
	i = 4;
	while (--i >= 0)
		temp[i] = file[--len];
	if (!(ft_strnstr(temp, ".ber", 4)))
		ft_error(vars, "Input '.ber' file", false);
	ft_get_map(vars, file);
	y = -1;
	ft_printf("Map:\n");
	while (vars->matrix[++y])
	{
		x = -1;
		while (vars->matrix[y][++x])
			ft_printf("%c", vars->matrix[y][x]);
		ft_printf("\n");
	}
	ft_verify_map(vars);
}
