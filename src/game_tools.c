/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 02:49:42 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 04:53:26 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	draw_xr(t_contr *contr)
{
	t_vpi width;
	t_vpi start;

	width = set_vpi(20, 4);
	start = set_vpi(contr->res.x / 2 - 10, contr->res.y / 2 - 2);
	draw_square_i(contr, start, width, 0x0000B3FF);
	start = set_vpi(contr->res.x / 2 - 2, contr->res.y / 2 - 10);
	width = set_vpi(5, 20);
	draw_square_i(contr, start, width, 0x0000B3FF);
}

int		dark_mode_mod(int color, float cur)
{
	t_color c;
	float	yo;

	c.r = 0xff0000 & color;
	c.g = 0xff00 & color;
	c.b = 0xff & color;
	yo = 1.0f - cur / VIEW_DIST;
	if (yo < 0.0f)
		yo = 0.0f;
	else if (yo > 1.0f)
		yo = 1.0f;
	c.r = ((int)((double)0x0 + (c.r - 0x0) * yo) & 0xFF0000);
	c.g = ((int)((double)0x0 + (c.g - 0x0) * yo) & 0xFF00);
	c.b = ((int)((double)0x0 + (c.b - 0x0) * yo) & 0xFF);
	return (c.r + c.g + c.b);
}

double	get_fov(t_contr *contr)
{
	return (0.50 / (1.0 * contr->res.y / (1.0 * contr->res.x)));
}

void	change_fov(t_contr *contr, int mode)
{
	if (mode == 1)
	{
		contr->plane.x = contr->plane.x / 1.25;
		contr->plane.y = contr->plane.y / 1.25;
		contr->dir.x = contr->dir.x * 1.25;
		contr->dir.y = contr->dir.y * 1.25;
		contr->sett.fov--;
	}
	else
	{
		contr->plane.x = contr->plane.x * 1.25;
		contr->plane.y = contr->plane.y * 1.25;
		contr->dir.x = contr->dir.x / 1.25;
		contr->dir.y = contr->dir.y / 1.25;
		contr->sett.fov++;
	}
}
