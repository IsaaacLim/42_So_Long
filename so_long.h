#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "Printf/includes/ft_printf.h"

# define SPEED 8

struct	s_img
{
	void	*ptr;
	int		wth;
	int		hgt;
	int		x;
	int		y;
	int		mask_x1;
	int		mask_x2;
	int		mask_y1;
	int		mask_y2;
	bool	mask_bot_right;
	int		count;
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
	bool			ended;
	struct s_img	bg;
	struct s_img	pc;
	struct s_img	en;
	struct s_img	wl;
	struct s_img	ext;
	struct s_img	clt;
}	t_data;

//Read file -> Get map
void	ft_get_map(t_data *vars, char *file);
void	ft_free_matrix(char **matrix, int height);

//MLX
void	ft_background(t_data *vars);
void	ft_close_window(t_data *vars);
void	ft_error(char *code, int i, t_data *vars);
int		ft_control(t_data *vars);
void	ft_cover_trails(t_data *vars, struct s_img *chr);

// Utils
int		ft_ternary(int yes, int i, int j);
int		ft_movement(int keycode, t_data *vars, struct s_img *obj);

//Other Functions
void	draw_square(t_data *vars);
void	my_mlx_pixel_put(t_data *vars, int x, int y, int color);

#endif



