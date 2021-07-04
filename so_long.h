#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "Printf/includes/ft_printf.h"

# include <stdio.h> //remove 

#define WIDTH 192//640
#define HEIGHT 192//480

/*typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;
*/
typedef struct	s_data
{
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*background;
	int		mask_x1;
	int		mask_x2;
	int		mask_y1;
	int		mask_y2;
	bool	mask_start;
	
	int		img_width;
	int		img_height;

	void	*player;
	int		player_width;
	int		player_height;
	
	int		shift_x;
	int		shift_y;

	void	*enemy;
	int		enemy_width;
	int		enemy_height; //create width and height then union for player, enemy
	float	test_x;

}	t_data;

//Read file -> Get map
void	ft_getmap(char *file);

void	my_mlx_pixel_put(t_data *vars, int x, int y, int color);
void	ft_background(t_data *vars);
void	ft_close_window(t_data *vars);
int		ft_control(t_data *vars);

//Other Functions
void	draw_square(t_data *vars);

#endif