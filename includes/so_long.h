#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx_int.h"

# ifndef NUM_OF_ENEMIES
#  define NUM_OF_ENEMIES 10
# endif

# ifndef ENEMY_POSITION
#  define ENEMY_POSITION 15
# endif

# define SPEED 8

struct	s_image
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
** | Move count		| Movement count, also used for alternating between images
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
	int		move_count;
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
	void	*img;
};

typedef struct s_data
{
	char			**matrix;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bbp;
	int				len;
	int				endian;
	int				win_wth;
	int				win_hgt;
	int				map_hgt;
	int				map_wth;
	int				items;
	bool			won;
	bool			lost;
	struct s_image	bg;
	struct s_image	wl;
	struct s_image	clt_0;
	struct s_image	clt_1;
	struct s_image	clt_2;
	struct s_image	ext0;
	struct s_image	ext1;
	struct s_image	en_0;
	struct s_image	en_1;
	struct s_image	pc_0;
	struct s_image	pc_w1;
	struct s_image	pc_w2;
	struct s_image	pc_s1;
	struct s_image	pc_s2;
	struct s_image	pc_a1;
	struct s_image	pc_a2;
	struct s_image	pc_d1;
	struct s_image	pc_d2;
	struct s_image	sc;
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

	int				(*p)(const char *, ...);
	int				(*put_img)(void *, void *, void *, int, int);
	void			*(*xpm_img)(void *, char *, int *, int *);
}	t_data;

//exit.c
int		ft_close_window(t_data *vars);
void	ft_error( t_data *vars, char *code, bool has_matrix);
void	ft_free_matrix(char **matrix, int height);

//ft_control_hook.c
int		ft_control_hook(t_data *vars);

//ft_init_vars.c
void	ft_init_vars(t_data *vars);

//ft_move_en.c
int		ft_movement_en(t_data vars, struct s_en *obj);

//ft_move_pc.c
int		ft_move_pc(t_data vars, struct s_pc *pc, int keycode);

//ft_parse_map.c
void	ft_parse_map(t_data *vars, char *file);

//ft_xpm_img.c
void	ft_xpm_img(t_data *vars);

//obj_enemy.c
void	ft_create_enemy(t_data *vars, int y, int x);
int		ft_en_loop(t_data *vars);

//obj_others.c
void	ft_map_img(t_data *vars);
void	ft_open_doors(t_data vars);
void	ft_put_steps(t_data vars);

//obj_player.c
void	ft_contact_collectible(t_data *vars, struct s_pc pc);
void	ft_cover_trails(t_data *vars, struct s_pc *pc);
void	ft_put_sprites(t_data vars, struct s_pc pc, int keycode);

#endif

/*
Game test
Exit only after collecting all collectibles
Run all around the map for image rendering
Random key presses
Closes window cleanly
Memory leaks

*/