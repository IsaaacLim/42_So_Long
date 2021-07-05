#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "Printf/includes/ft_printf.h"

# include <stdio.h> //remove 

# define WIDTH 192//640
# define HEIGHT 192//480

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
	int		x2;
	int		y2;
};

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			**matrix;
	int				win_wth;
	int				win_hgt;
	int				map_hgt;
	int				map_wth;
	int				items;
	struct s_img	bg;
	struct s_img	pc;
	struct s_img	en;
}	t_data;

//Read file -> Get map
void	ft_get_map(t_data *vars, char *file);
void	ft_free_matrix(char **matrix, int height);

void	ft_background(t_data *vars);
void	ft_close_window(t_data *vars);
void	ft_error(char *code, int i, t_data *vars);
int		ft_control(t_data *vars);

//Other Functions
void	draw_square(t_data *vars);
void	my_mlx_pixel_put(t_data *vars, int x, int y, int color);

#endif



