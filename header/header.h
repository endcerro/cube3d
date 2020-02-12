/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/12 08:36:52 by edal--ce         ###   ########.fr       */
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
# include <fcntl.h>
# include "mlx.h"

# include "../libft/libft.h"


#define MULTIVECT 25.0
#define WHITE = 0x00FFFFFF
#define RED = 0xFF000000
#define BLUE = 0x000000FF
#define GREEN = 0x0000FF00

typedef struct s_vp
{
	double x;
	double y;
}				t_vp;


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
	// char			tx_NO;
	// char			tx_NO;
	// char			tx_NO;
	// char			tx_NO;
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

}					t_contr;



int		get_next_line(int fd, char **line);
void    load_map(char *filename, t_contr *contr);
int 	draw_top_down_map(t_contr *contr);
int		ft_abs(int val);
double 	ft_abs_double(double val);
void 	dda(t_contr *contr);
void 	handle_keys(t_contr *contr);
int 	close_(t_contr *contr, char *message);
void    p_px(t_contr *contr, int x, int y, int color);
void 	print_image(t_contr *contr, int x, int y);
void 	draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color);
void 	load_cub(char *filename, t_contr *contr);
unsigned int    	g_px(t_text text, int x, int y);
int 	key_press(int key, t_contr *param);
int 	key_release(int key, t_contr *contr);
int	ft_isdigit(int c);
int get_screenshot(t_contr *contr);
void load_cub(char *filename, t_contr* contr);
void texture_loadr(char *path, t_contr *contr);
void spritecast(t_contr *contr, double *ZBuffer);

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
// typedef enum		e_key_code
// {
// 	LEFT_CLICK = 1,
// 	RIGHT_CLICK = 2,
// 	SCROLL_UP = 4,
// 	SCROLL_DOWN = 5,
// 	ZOOM_IN = 69,
// 	ZOOM_OUT = 78,
// 	SPACE = 49,
// 	NUM_LOCK_9 = 92,
// 	NUM_LOCK_8 = 91,
// 	NUM_LOCK_7 = 89,
// 	NUM_LOCK_6 = 88,
// 	NUM_LOCK_5 = 87,
// 	NUM_LOCK_4 = 86,
// 	NUM_LOCK_3 = 85,
// 	NUM_LOCK_2 = 84,
// 	NUM_LOCK_1 = 83,
// 	NUM_LOCK_0 = 82,
// 	RIGHT_ARROW = 124,
// 	LEFT_ARROW = 123,
// 	UP_ARROW = 126,
// 	DOWN_ARROW = 125,
// }					t_key_code;


#endif
