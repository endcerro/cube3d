/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/17 20:48:21 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <pthread.h>
# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <stdio.h>

# include <math.h>
# include "mlx.h"

# include "../libft/libft.h"


# define MULTIVECT 25.0
# define WHITE = 0x00FFFFFF
# define RED = 0xFF000000
# define BLUE = 0x000000FF
# define GREEN = 0x0000FF00
# define VIEW_DIST 8

typedef struct s_vp
{
	double x;
	double y;
}				t_vp;

typedef struct s_vpi
{
	int x;
	int y;
}				t_vpi;

typedef struct s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct s_col_rend
{
	t_vpi draw_v;
	t_vp tex_m;
	t_vp side_dist;
	t_vp delta_dist;
	t_vpi step;
	t_vp		pos; 
	t_vp		dir;
	t_vp		plane;
	t_vp 		ray_dir;
	t_vpi		map;
	double 		*z_buffer;
	double 		wallX;
	int 		side;
	int 		lineHeight;
	// int x;
	int tx_id;
	double tx_step;
	int x;
	double perpWallDist;

}				t_col_rend;
typedef struct s_img
{
	int     bpp;
	int     length;
	int     endian;
	void	*img;
	char 	*addr;
}				t_img;

typedef	struct s_text
{
	t_img 	texture;
	int 	w;
	int 	h;
}				t_text;

typedef	struct s_sprite
{
	t_text 	texture;
	double 	x;
	double 	y;
}				t_sprite;

typedef struct s_key
{
	char	w	:1;
	char	a	:1;
	char	s	:1;
	char	d	:1;
	char	q	:1;
	char	e	:1;
}				t_key;

typedef struct		s_contr
{
	int				c_color;
	int				f_color;
	int				screen;
	t_text			textures[20];
	t_sprite 		sprites[20];
	t_img			img;
	void			*mlx;
	void			*win_ptr;
	char 			**map;
	int 			res_w;
	int				res_h;
	int 			map_w;
	int 			map_h;
	int				text_nb;
	int				sprites_nb;
	t_key			key;
	t_vp 			pos;
	t_vp 			dir;
	t_vp 			plane;
	int				dark_mode;
	// t_color			c_color;

}					t_contr;



int				get_next_line(int fd, char **line);
void    		load_map(char *filename, t_contr *contr);
int 			draw_top_down_map(t_contr *contr);
int				ft_abs(int val);
double 			ft_abs_double(double val);
void 			dda(t_contr *contr);
void 			handle_keys(t_contr *contr);
int 			close_(t_contr *contr, char *message);
void    		p_px(t_contr *contr, int x, int y, int color);
void 			print_image(t_contr *contr, int x, int y);
void 			draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color);
void 			load_cub(char *filename, t_contr *contr);
unsigned int    g_px(t_text text, int x, int y);
int 			key_press(int key, t_contr *param);
int 			key_release(int key, t_contr *contr);
int				ft_isdigit(int c);
void 			get_screenshot(t_contr *contr);
void 			load_cub(char *filename, t_contr* contr);
void 			texture_loadr(char *path, t_contr *contr);
void 			spritecast(t_contr *contr, double *ZBuffer);
int				check_fw_bw(t_contr *contr, char c, double move_speed);
int				check_str_(t_contr *contr, double move_speed, int dir);
void			rotate(t_contr *contr, int dir, double rot_speed);
void get_text_NO(char *line, t_contr *contr);//, int val)
void get_text_SO(char *line, t_contr *contr);//, int val)
void get_text_EA(char *line, t_contr *contr);//, int val)
void get_text_WE(char *line, t_contr *contr);//, int val)
void get_text_SPR(char *line, t_contr *contr);//, int val)
void	drawback(t_contr* contr);
void	draw_floor(t_contr *contr);
int			hit_wall(t_contr *contr, t_col_rend *r, t_vpi *map);
int			get_tx_id(int side, t_vpi step);
void		init_r(t_contr *contr, t_col_rend *r);
t_col_rend	draw_bc(t_contr *contr);


typedef struct __attribute__((__packed__)) s_bmp_fhead 
{
	unsigned char 	type[2];
	int 			file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset;
}	t_bmp_fhead;
typedef struct __attribute__((__packed__)) s_bmp_ihead 
{
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
} t_bmp_ihead;
// typedef enum		e_event_code
// {
// 	MOUSE_PRESS_CODE = 4,
// 	MOUSE_MOVE_CODE = 6,
// 	KEY_PRESS_CODE = 2,
// 	KEY_RELEASE_CODE = 3,
// 	RED_BUTTON_CODE = 17,
// }					t_event_code;
// typedef enum		e_ft_mlx_hooks
// {
// 	NO_EVENT_HOOK = 0,
// 	MOUSE_PRESS_HOOK = 1,
// 	MOUSE_MOVE_HOOK = 2,
// 	KEY_PRESS_HOOK = 4,
// 	RED_BUTTON_HOOK = 8,
// }					t_ft_mlx_hooks;
typedef enum		e_key_code
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
	ZOOM_IN = 69,
	ZOOM_OUT = 78,
	SPACE = 49,
	NUM_LOCK_9 = 92,
	NUM_LOCK_8 = 91,
	NUM_LOCK_7 = 89,
	NUM_LOCK_6 = 88,
	NUM_LOCK_5 = 87,
	NUM_LOCK_4 = 86,
	NUM_LOCK_3 = 85,
	NUM_LOCK_2 = 84,
	NUM_LOCK_1 = 83,
	NUM_LOCK_0 = 82,
	RIGHT_ARROW = 124,
	LEFT_ARROW = 123,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
}					t_key_code;


#endif
