/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 20:01:03 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <stdio.h>

# include <math.h>
# include "mlx.h"

# include "../libft/libft.h"

# define VIEW_DIST 8

typedef struct __attribute__((__packed__))	s_bmp_fhead
{
	unsigned char	type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset;
}											t_bmp_fhead;

typedef struct __attribute__((__packed__))	s_bmp_ihead
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}											t_bmp_ihead;

typedef struct								s_img
{
	int		bpp;
	int		length;
	int		endian;
	void	*img;
	char	*addr;
}											t_img;

typedef struct								s_vp
{
	double	x;
	double	y;
}											t_vp;

typedef struct								s_vpi
{
	int		x;
	int		y;
}											t_vpi;

typedef struct								s_color
{
	int		r;
	int		g;
	int		b;
}											t_color;

typedef struct								s_col_rend
{
	t_vpi		draw_v;
	t_vpi		step;
	t_vpi		map;
	t_vp		tex_m;
	t_vp		side_dist;
	t_vp		delta_dist;
	t_vp		pos;
	t_vp		dir;
	t_vp		plane;
	t_vp		ray_dir;
	double		*z_buffer;
	double		wall_x;
	double		tx_step;
	int			side;
	int			line_h;
	int			tx_id;
	int			x;
	double		perp_w_dst;
}											t_col_rend;

typedef	struct								s_text
{
	t_img	texture;
	int		w;
	int		h;
}											t_text;

typedef	struct								s_sprite
{
	t_text	texture;
	double	x;
	double	y;
}											t_sprite;

typedef struct								s_floor_rend
{
	t_vp	dir;
	t_vp	plane;
	t_vp	pos;
	t_vp	floor;
	t_vpi	tx_m;
	t_vp	floor_step;
	double	pos_r;
}											t_floor_rend;

typedef struct								s_sprite_rend
{
	int			sprites_nb;
	int			*spr_ord;
	double		*spr_dst;
	t_vp		dir;
	t_vp		pos;
	t_vp		plane;
	t_vp		transform;
	t_vpi		draw_start;
	t_vpi		draw_end;
	t_vp		sprite;
	t_vpi		sprite_d;
	t_vpi		tex_p;
	t_sprite	*sprites;
	double		*z_buff;
	int			spr_screen_x;
}											t_sprite_rend;

typedef struct								s_key
{
	char	w	:1;
	char	a	:1;
	char	s	:1;
	char	d	:1;
	char	q	:1;
	char	e	:1;
}											t_key;

typedef struct								s_options
{
	double	move_speed;
	double	rot_speed;
	double	fov;
	int		selected;
}											t_options;

typedef struct								s_contr
{
	char			basic_sprites[5];
	int				c_color;
	int				f_color;
	int				screen;
	t_text			textures[20];
	t_text			weapons[2];
	t_sprite		sprites[20];
	int				enn_id;
	t_img			img;
	void			*mlx;
	void			*win_ptr;
	char			**map;
	t_vpi			res;
	t_vpi			mpd;
	int				tx_nb;
	int				sprites_nb;
	t_key			key;
	t_vp			pos;
	t_vp			dir;
	t_vp			plane;
	int				menu_mode;
	int				dark_mode;
	int				hp;
	t_options		sett;
	int				atk_frame;
}											t_contr;

void			load_cub(char *filename, t_contr *contr);
void			texture_loadr(char *path, t_contr *contr, int index);
void			get_text_no(char *line, t_contr *contr);
void			get_text_so(char *line, t_contr *contr);
void			get_text_ea(char *line, t_contr *contr);
void			get_text_we(char *line, t_contr *contr);
void			get_text_spr(char *line, t_contr *contr);
void			set_n(t_contr *contr, int i, int j);
void			set_s(t_contr *contr, int i, int j);
void			set_e(t_contr *contr, int i, int j);
void			set_w(t_contr *contr, int i, int j);
double			get_fov(t_contr *contr);
void			sub_load(t_contr *contr, int i);
void			parseline(char *line, t_contr *contr, int *val);
void			parse_sprites(t_contr *contr);
int				parse_map(t_contr *contr);
int				key_press(int key, t_contr *param);
int				key_release(int key, t_contr *contr);
unsigned int	g_px(t_text text, int x, int y);
void			p_px(t_contr *contr, int x, int y, int color);
int				mouse_(int btn, int x, int y, t_contr *contr);
void			handle_keys(t_contr *contr);
void			wall_cast(t_contr *contr);
void			spritecast(t_contr *contr, double *z_buff);
void			drawback(t_contr *contr);
void			draw_floor(t_contr *contr);
void			draw_minmap(t_contr *contr);
int				hit_wall(t_contr *contr, t_col_rend *r, t_vpi *map);
void			init_r(t_contr *contr, t_col_rend *r);
t_col_rend		draw_bc(t_contr *contr);
int				check_fw_bw(t_contr *contr, char c, double move_speed);
int				check_str_(t_contr *contr, double move_speed, int dir);
void			rotate(t_contr *contr, int dir, double rot_speed);
void			change_fov(t_contr *contr, int mode);
int				close_(t_contr *contr, char *message);
void			print_image(t_contr *contr, int x, int y);
void			get_screenshot(t_contr *contr);
int				get_tx_id(int side, t_vpi step);
int				dark_mode_mod(int color, float cur);
unsigned int	g_vpx(t_text tx, t_vpi pos);
int				vpi_norm(t_vpi v);
double			vp_norm(t_vp v);
void			sort_sprites(double *spr_d, int *spr_o, int c);
void			draw_square(t_contr *contr, t_vpi start, t_vpi len, int color);
void			draw_square_i(t_contr *contr, t_vpi strt, t_vpi len, int color);
t_vp			set_vp(double x, double y);
t_vpi			set_vpi(int x, int y);
int				get_rdm(int lower, int upper);
void			respawn_enn(t_contr *contr);
void			check_hit(t_contr *contr);
void			prep_game(t_contr *contr);
void			move_spr(t_contr *contr);
void			show_sett(t_contr *contr);
void			print_menu(t_contr *contr, int x, int y);
void			draw_wpn(t_contr *contr);
void			load_wpns(t_contr *contr);
void			free_mand(t_contr *contr);
void			get_fc_colors(char *line, t_contr *contr);
void			menu_mode(t_contr *contr);

#endif
