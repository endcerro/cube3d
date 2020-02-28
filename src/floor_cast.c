/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:26:46 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 04:53:09 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	drawback(t_contr *contr)
{
	int floor;
	int ceil;
	int x;
	int y;

	floor = contr->f_color;
	ceil = contr->c_color;
	y = -1;
	while (++y < contr->res.y / 2)
	{
		x = -1;
		while (++x < contr->res.x)
			p_px(contr, x, y, ceil);
	}
	while (++y < contr->res.y)
	{
		x = -1;
		while (++x < contr->res.x)
			p_px(contr, x, y, floor);
	}
}

void	draw_floor_ceil(t_contr *contr, t_floor_rend *r, int y)
{
	int		x;
	int		color;
	t_vpi	tx_m;

	x = -1;
	while (++x < contr->res.x - 1)
	{
		tx_m.x = (int)(64 * (r->floor.x - (int)r->floor.x)) & (64 - 1);
		tx_m.y = (int)(64 * (r->floor.y - (int)r->floor.y)) & (64 - 1);
		color = g_px(contr->textures[5], tx_m.x, tx_m.y);
		if ((r->floor.x += r->floor_step.x) && contr->dark_mode == 1)
			color = dark_mode_mod(color, contr->res.y /
				(2.0f * y - contr->res.y));
		p_px(contr, x, y, color);
		color = g_px(contr->textures[6], tx_m.x, tx_m.y);
		if ((r->floor.y += r->floor_step.y) && contr->dark_mode == 1)
			color = dark_mode_mod(color, contr->res.y /
				(2.0f * y - contr->res.y));
		p_px(contr, x, contr->res.y - y - 1, color);
	}
}

void	draw_floor(t_contr *contr)
{
	t_floor_rend	r;
	int				y;
	int				p;
	t_vp			ray_0;
	t_vp			ray_1;

	y = -1;
	while (++y < contr->res.y)
	{
		ray_0.x = contr->dir.x - contr->plane.x;
		ray_0.y = contr->dir.y - contr->plane.y;
		ray_1.x = contr->dir.x + contr->plane.x;
		ray_1.y = contr->dir.y + contr->plane.y;
		p = y - contr->res.y / 2;
		r.pos_r = 0.5 * contr->res.y;
		r.floor_step.x = r.pos_r / p * (ray_1.x - ray_0.x) / contr->res.x;
		r.floor_step.y = r.pos_r / p * (ray_1.y - ray_0.y) / contr->res.x;
		r.floor.x = contr->pos.x + r.pos_r / p * ray_0.x;
		r.floor.y = contr->pos.y + r.pos_r / p * ray_0.y;
		draw_floor_ceil(contr, &r, y);
	}
}
