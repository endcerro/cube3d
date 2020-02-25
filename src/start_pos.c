/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:55:41 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 00:05:42 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	set_n(t_contr *contr, int i, int j)
{
	contr->pos.x = j + 0.5;
	contr->pos.y = i + 0.5;
	contr->dir.x = 0;
	contr->dir.y = -1;
	contr->plane.x = 0.66;
	contr->plane.x = get_fov(contr);
	contr->plane.y = 0;
	contr->map[i][j] = '0';
}

void	set_s(t_contr *contr, int i, int j)
{
	contr->pos.x = j + 0.5;
	contr->pos.y = i + 0.5;
	contr->dir.x = 0;
	contr->dir.y = 1;
	contr->plane.x = -0.66;
	contr->plane.x = -get_fov(contr);
	contr->plane.y = 0;
	contr->map[i][j] = '0';
}

void	set_e(t_contr *contr, int i, int j)
{
	contr->pos.x = j + 0.5;
	contr->pos.y = i + 0.5;
	contr->dir.x = 1;
	contr->dir.y = 0;
	contr->plane.x = 0;
	contr->plane.y = 0.66;
	contr->plane.y = get_fov(contr);
	contr->map[i][j] = '0';
}

void	set_w(t_contr *contr, int i, int j)
{
	contr->pos.x = j + 0.5;
	contr->pos.y = i + 0.5;
	contr->dir.x = -1;
	contr->dir.y = 0;
	contr->plane.x = 0;
	contr->plane.y = -0.66;
	contr->plane.y = -get_fov(contr);
	contr->map[i][j] = '0';
}
