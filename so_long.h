#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "Printf/includes/ft_printf.h"

# ifndef NUM_OF_ENEMIES
#  define NUM_OF_ENEMIES 10
# endif

# ifndef EN_NUM
#  define EN_NUM 15
# endif

# define SPEED 8

struct	s_img
{
	void	*ptr;
	int		wth;
	int		hgt;
};

/*
** STRUCT FOR PLAYER CHARACTER
** | x, y		| Current position (multiplied by image size)
** | x_up, y_up	| Current position (rounded up matrix value)
** | m_*		| Previous position of 4 quarters used for masking
** | count		| Movement count, also used for alternating between images
*/
struct s_pc
{
	int		x;
	int		y;
	int		x_up;
	int		y_up;
	int		m_x1;
	int		m_y1;
	int		m_x2;
	int		m_y2;
	int		count;
};

/*
** STRUCT FOR ENEMY CHARACTER
** | x, y		| Current position
** | m_*		| Previous position if x/y axis used for masking
** | dir		| Movement direction
** | rank		| Variation for <dir>, also used to check if en_clone exist
** | counter	| Timer to execute a movement
** | speed		| Movement Speed
*/
struct s_en
{
	int		x;
	int		y;
	int		m_x1;
	int		m_y1;
	char	dir;
	int		rank;
	int		counter;
	int		speed;
};

typedef struct s_data
{
	char			**matrix;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				win_wth;
	int				win_hgt;
	int				map_hgt;
	int				map_wth;
	int				items;
	bool			ended;
	struct s_img	bg;
	struct s_img	wl;
	struct s_img	ext;
	struct s_img	clt;
	struct s_img	pc_0;
	struct s_img	en_0;
	struct s_pc		pc;
	struct s_en		en1;
	struct s_en		en2;
	struct s_en		en3;
	struct s_en		en4;
	struct s_en		en5;
	struct s_en		en6;
	struct s_en		en7;
	struct s_en		en8;
	struct s_en		en9;
	struct s_en		en10;
}	t_data;

//Read file -> Get map
void	ft_get_map(t_data *vars, char *file);
void	ft_free_matrix(char **matrix, int height);

//MLX
void	ft_background(t_data *vars);
void	ft_close_window(t_data *vars);
void	ft_error(char *code, int i, t_data *vars);
int		ft_control(t_data *vars);
void	ft_cover_trails(t_data *vars, struct s_pc *obj);

// Utils
int		ft_ternary(int yes, int i, int j);
int		ft_movement_pc(int keycode, t_data *vars, struct s_pc *obj);
int		ft_movement_en(t_data *vars, struct s_en *obj);
bool	ft_contact_enemy(t_data *vars, struct s_pc pc, struct s_en en);

//Other Functions
void	draw_square(t_data *vars);
void	my_mlx_pixel_put(t_data *vars, int x, int y, int color);

#endif

/*
TO DO:
1. Add window counter
	Set 4 images to print
	if count % 10 = x -> number
	if count / 10 % 10 = x && if count < 10 print 0
	if count / 100 % 10 && if count < 100 print 0
	if count / 100 = x && if count < 1000 print 0
2. Add -D ENEMY_NUMBER & -D POSITION_NUMBER
	- Substitude variables in file to accept
3. Add make file to accept -D
4. Make file print message to inform how to specify
5. Simplify ft_init_enemy to take in 10 enemies
*/