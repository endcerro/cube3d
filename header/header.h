/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 11:23:44 by user42           ###   ########.fr       */
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

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "structs.h"
# include "screen.h"
# define VIEW_DIST 8

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
void			sub_load(t_contr *contr, int i);
void			parse_sprites(t_contr *contr);
void			p_px(t_contr *contr, int x, int y, int color);
void			handle_keys(t_contr *contr);
void			wall_cast(t_contr *contr);
void			spritecast(t_contr *contr, double *z_buff);
void			drawback(t_contr *contr);
void			draw_floor(t_contr *contr);
void			draw_minmap(t_contr *contr);
void			check_hit(t_contr *contr);
void			prep_game(t_contr *contr);
void			move_enn(t_contr *contr);
void			draw_wpn(t_contr *contr);
void			load_wpns(t_contr *contr);
void			free_mand(t_contr *contr);
void			get_fc_colors(char *line, t_contr *contr);
void			menu_mode(t_contr *contr);
void			free_after(t_contr *contr, int i);
void			init_game(t_contr *contr);
void			draw_hp(t_contr *contr);
void			draw_drk_b(t_contr *contr);
void			sort_sprites(double *spr_d, int *spr_o, int c);
void			draw_square(t_contr *contr, t_vpi start, t_vpi len, int color);
void			draw_square_i(t_contr *contr, t_vpi strt, t_vpi len, int color);
void			print_image(t_contr *contr, int x, int y);
void			get_screenshot(t_contr *contr);
void			init_r(t_contr *contr, t_col_rend *r);
void			rotate(t_contr *contr, int dir, double rot_speed);
void			change_fov(t_contr *contr, int mode);
void			draw_xr(t_contr *contr);
double			get_fov(t_contr *contr);
double			vp_norm(t_vp v);
int				parse_map(t_contr *contr);
int				key_press(int key, t_contr *param);
int				key_release(int key, t_contr *contr);
int				check_fw_bw(t_contr *contr, char c, double move_speed);
int				check_str_(t_contr *contr, double move_speed, int dir);
int				close_(t_contr *contr, char *message);
int				get_tx_id(int side, t_vpi step);
int				dark_mode_mod(int color, float cur);
int				vpi_norm(t_vpi v);
int				mouse_(int btn, int x, int y, t_contr *contr);
int				hit_wall(t_contr *contr, t_col_rend *r, t_vpi *map);
unsigned int	g_px(t_text text, int x, int y);
unsigned int	g_vpx(t_text tx, t_vpi pos);
t_col_rend		draw_bc(t_contr *contr);
t_col_rend		draw_bcb(t_contr *contr);
t_vp			set_vp(double x, double y);
t_vpi			set_vpi(int x, int y);
char			**grow_map(t_contr *contr);
int				check_if_closed(t_contr *contr, char **map);
void			flood_fill(t_contr *contr, int i, int j, char **map);
void			free_tmp(char **tmp, int d);
int				close_hook(t_contr *contr);
int				check_init(t_contr *contr);
void 			prep_check(t_contr *contr);

#endif
