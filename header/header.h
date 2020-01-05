/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:25:23 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/05 07:14:15 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <stdio.h>


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


}					t_contr;

int		get_next_line(int fd, char **line);
void    load_map(char *filename, t_contr *contr);
int 	draw_top_down_map(t_contr *contr);
int					ft_abs(int val);
double ft_abs_double(double val);

#endif
