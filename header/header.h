/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/06 18:16:55 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <stdio.h>

#define WHITE 0x00FFFFFF
#define RED = 0xFF000000;
#define BLUE = 0x000000FF;
#define GREEN = 0x0000FF00;

typedef struct s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_dpoint
{
	double x;
	double y;
}				t_dpoint;


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
	int 			res_w;
	int				res_h;
	void			*mlx_ptr;
	void			*win_ptr;
	int 			map_w;
	int 			**map;
	double 			p_x;
	double 			p_y;
	double 			dir_x;
	double 			dir_y;
	double 			planeX;
	double 			planeY;

	t_img			img;

	int pas_x;
	int pas_y;

	int value;
}					t_contr;

int		get_next_line(int fd, char **line);
void    load_map(char *filename, t_contr *contr);
int 	draw_top_down_map(t_contr *contr);
int					ft_abs(int val);
double ft_abs_double(double val);

#endif
