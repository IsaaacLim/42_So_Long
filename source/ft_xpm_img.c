#include "../so_long.h"

/*
** Just to store image pointer
** Function split just because of norminette
** Sprites:
**	Utils - Background (bg), Wall (wl), Exit (ext), Step Count background (sc)
**	Contact - Enemies (en), Collectables (clt)
**	PC - Player Character Sprites (pc) 
*/

static void	ft_pc_sprites_1(t_data *v)
{
	char	*pc_0;
	char	*pc_w1;
	char	*pc_w2;
	char	*pc_s1;
	char	*pc_s2;

	pc_0 = "images/yoshi_0_bg.xpm";
	pc_w1 = "images/yoshi_b1_bg.xpm";
	pc_w2 = "images/yoshi_b2_bg.xpm";
	pc_s1 = "images/yoshi_f1_bg.xpm";
	pc_s2 = "images/yoshi_f2_bg.xpm";
	v->pc_0.ptr = v->xpm_img(v->mlx, pc_0, &v->pc_0.wth, &v->pc_0.hgt);
	v->pc_w1.ptr = v->xpm_img(v->mlx, pc_w1, &v->pc_w1.wth, &v->pc_w1.hgt);
	v->pc_w2.ptr = v->xpm_img(v->mlx, pc_w2, &v->pc_w2.wth, &v->pc_w2.hgt);
	v->pc_s1.ptr = v->xpm_img(v->mlx, pc_s1, &v->pc_s1.wth, &v->pc_s1.hgt);
	v->pc_s2.ptr = v->xpm_img(v->mlx, pc_s2, &v->pc_s2.wth, &v->pc_s2.hgt);
}

static void	ft_pc_sprites_2(t_data *v)
{
	char	*pc_a1;
	char	*pc_a2;
	char	*pc_d1;
	char	*pc_d2;

	pc_a1 = "images/yoshi_l1_bg.xpm";
	pc_a2 = "images/yoshi_l2_bg.xpm";
	pc_d1 = "images/yoshi_r1_bg.xpm";
	pc_d2 = "images/yoshi_r2_bg.xpm";
	v->pc_a1.ptr = v->xpm_img(v->mlx, pc_a1, &v->pc_a1.wth, &v->pc_a1.hgt);
	v->pc_a2.ptr = v->xpm_img(v->mlx, pc_a2, &v->pc_a2.wth, &v->pc_a2.hgt);
	v->pc_d1.ptr = v->xpm_img(v->mlx, pc_d1, &v->pc_d1.wth, &v->pc_d1.hgt);
	v->pc_d2.ptr = v->xpm_img(v->mlx, pc_d2, &v->pc_d2.wth, &v->pc_d2.hgt);
}

static void	ft_contact_sprites(t_data *v)
{
	char	*clt_0;
	char	*clt_l;
	char	*clt_r;
	char	*en_0;
	char	*en_1;

	clt_0 = "images/egg_up.xpm";
	clt_l = "images/egg_left.xpm";
	clt_r = "images/egg_right.xpm";
	en_0 = "images/gomba1.xpm";
	en_1 = "images/gomba2.xpm";
	v->clt_0.ptr = v->xpm_img(v->mlx, clt_0, &v->clt_0.wth, &v->clt_0.hgt);
	v->clt_l.ptr = v->xpm_img(v->mlx, clt_l, &v->clt_l.wth, &v->clt_l.hgt);
	v->clt_r.ptr = v->xpm_img(v->mlx, clt_r, &v->clt_r.wth, &v->clt_r.hgt);
	v->en_0.ptr = v->xpm_img(v->mlx, en_0, &v->en_0.wth, &v->en_0.hgt);
	v->en_1.ptr = v->xpm_img(v->mlx, en_1, &v->en_1.wth, &v->en_1.hgt);
}

static void	ft_utils_sprites(t_data *v)
{
	char	*bg;
	char	*wl;
	char	*ext0;
	char	*ext1;
	char	*sc;

	bg = "images/ground_tile.xpm";
	wl = "images/wall.xpm";
	ext0 = "images/door_close.xpm";
	ext1 = "images/door_open.xpm";
	sc = "images/steps_bg.xpm";
	v->bg.ptr = v->xpm_img(v->mlx, bg, &v->bg.wth, &v->bg.hgt);
	v->wl.ptr = v->xpm_img(v->mlx, wl, &v->wl.wth, &v->wl.hgt);
	v->ext0.ptr = v->xpm_img(v->mlx, ext0, &v->ext0.wth, &v->ext0.hgt);
	v->ext1.ptr = v->xpm_img(v->mlx, ext1, &v->ext1.wth, &v->ext1.hgt);
	v->sc.ptr = v->xpm_img(v->mlx, sc, &v->sc.wth, &v->sc.hgt);
}

void	ft_xpm_img(t_data *v)
{
	ft_utils_sprites(v);
	ft_contact_sprites(v);
	ft_pc_sprites_1(v);
	ft_pc_sprites_2(v);
}
