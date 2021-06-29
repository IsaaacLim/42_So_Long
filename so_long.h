#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
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
}	t_data;

#endif