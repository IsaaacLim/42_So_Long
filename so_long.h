#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h> //remove 

#define WIDTH 640
#define HEIGHT 480

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

	int		img_width;
	int		img_height;

	int		shift_x;
	int		shift_y;
}	t_data;

void	my_mlx_pixel_put(t_data *vars, int x, int y, int color);
void	ft_close_window(t_data *vars);
int		ft_control(t_data *vars);

//Other Functions
void	draw_square(t_data *vars);

#endif