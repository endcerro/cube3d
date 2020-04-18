/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:58:33 by user42            #+#    #+#             */
/*   Updated: 2020/04/18 11:08:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct								s_img
{
	int				bpp;
	int				length;
	int				endian;
	void			*img;
	char			*addr;
}											t_img;

typedef struct								s_vp
{
	double			x;
	double			y;
}											t_vp;

typedef struct								s_vpi
{
	int				x;
	int				y;
}											t_vpi;

typedef struct								s_color
{
	int				r;
	int				g;
	int				b;
}											t_color;

typedef struct								s_col_rend
{
	t_vpi			draw_v;
	t_vpi			step;
	t_vpi			map;
	t_vp			tex_m;
	t_vp			side_dist;
	t_vp			delta_dist;
	t_vp			pos;
	t_vp			dir;
	t_vp			plane;
	t_vp			ray_dir;
	double			*z_buffer;
	double			wall_x;
	double			tx_step;
	int				side;
	int				line_h;
	int				tx_id;
	int				x;
	double			perp_w_dst;
}											t_col_rend;

typedef	struct								s_text
{
	t_img			texture;
	int				w;
	int				h;
}											t_text;

typedef	struct								s_sprite
{
	t_text			texture;
	double			x;
	double			y;
}											t_sprite;

typedef struct								s_floor_rend
{
	t_vp			dir;
	t_vp			plane;
	t_vp			pos;
	t_vp			floor;
	t_vpi			tx_m;
	t_vp			floor_step;
	double			pos_r;
}											t_floor_rend;

typedef struct								s_sprite_rend
{
	int				sprites_nb;
	int				*spr_ord;
	double			*spr_dst;
	t_vp			dir;
	t_vp			pos;
	t_vp			plane;
	t_vp			transform;
	t_vpi			draw_start;
	t_vpi			draw_end;
	t_vp			sprite;
	t_vpi			sprite_d;
	t_vpi			tex_p;
	t_sprite		*sprites;
	double			*z_buff;
	int				spr_screen_x;
}											t_sprite_rend;

typedef struct								s_key
{
	char			w	:1;
	char			a	:1;
	char			s	:1;
	char			d	:1;
	char			q	:1;
	char			e	:1;
}											t_key;

typedef struct								s_options
{
	double			move_speed;
	double			rot_speed;
	double			fov;
	int				selected;
}											t_options;

typedef struct								s_parse
{
	int				res;
	int				tx_n;
	int				tx_s;
	int				tx_e;
	int				tx_w;
	int				c_f;
	int				c_c;
	int				spr;
}											t_parse;


typedef struct								s_contr
{
	t_parse			map_parser;
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
	int				score;
	int				bonus;
}											t_contr;

#endif
