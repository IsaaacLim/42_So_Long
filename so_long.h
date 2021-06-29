#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>

#define WIDTH 960
#define HEIGHT 540

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

#endif