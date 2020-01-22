/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 04:39:54 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <stdio.h>

# include <math.h>

# include "mlx.h"

# include "../libft/libft.h"


#define MULTIVECT 25.0
#define WHITE = 0x00FFFFFF
#define RED = 0xFF000000
#define BLUE = 0x000000FF
#define GREEN = 0x0000FF00

typedef struct 	s_vect
{
	double 		x;
	double 		y;
}				t_vect;

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

typedef struct		s_contr
{
	t_img			img;
	void			*mlx;
	void			*win_ptr;
	int 			**map;
	int 			res_w;
	int				res_h;
	int 			map_w;
	t_vp 			pos;
	t_vp 			dir;
	t_vp 			plane;
}					t_contr;



int		get_next_line(int fd, char **line);
void    load_map(char *filename, t_contr *contr);
int 	draw_top_down_map(t_contr *contr);
int		ft_abs(int val);
double 	ft_abs_double(double val);
void dda(t_contr *contr);


void    p_px(t_contr *contr, int x, int y, int color);
void 	print_image(t_contr *contr, int x, int y);
void 	draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color);


int 	key_press(int key, t_contr *param);
//int draw_top_down_map(t_contr *contr);
//int draw_square(double x_0, double y_0, double x_e, double y_e, t_contr *contr, int color);
//void draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color){;


#endif
