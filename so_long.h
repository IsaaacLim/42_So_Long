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

struct	s_img
{
	void	*ptr;
	int		wth;
	int		hgt;
	union {
		int		x;
		float	X;
	};
	union {
		int		y;
		float	Y;
	};
};

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	struct s_img bg;
	struct s_img pc;
	struct s_img en;

	int		mask_x1;
	int		mask_x2;
	int		mask_y1;
	int		mask_y2;
	bool	mask_start;
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