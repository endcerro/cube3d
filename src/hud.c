/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 02:36:55 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 02:47:51 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	draw_wpn(t_contr *contr)
{
	t_vpi	pos;
	t_vpi	draw_p;
	t_vp	stp;
	int		spr_id;
	int		clr;

	spr_id = (contr->atk_frame > 1) ? 1 : 0;
	pos = set_vpi(0, 0);
	draw_p = set_vpi(0, contr->res.y - contr->res.y / 2 - 1);
	stp.x = 1.0 * (contr->res.x / 2) / contr->weapons[spr_id].w;
	stp.y = 1.0 * (contr->res.y / 2) / contr->weapons[spr_id].h;
	while (++draw_p.y < contr->res.y)
	{
		pos.x = 0;
		draw_p.x = contr->res.x - contr->res.x / 2 - 1;
		while (++draw_p.x < contr->res.x)
		{
			clr = g_px(contr->weapons[spr_id], pos.x++ / stp.x, pos.y / stp.y);
			if (clr != 0x00000000)
				p_px(contr, draw_p.x, draw_p.y, clr);
		}
		pos.y++;
	}
	if (contr->atk_frame > 0)
		contr->atk_frame--;
}

void	draw_drk_b(t_contr *contr)
{
	t_vpi t;
	t_vpi t2;

	t.x = 250;
	t.y = 260;
	t2.x = 40;
	t2.y = 40;
	draw_square(contr, t, t2, 0x00FFFFFF);
	if (contr->dark_mode == 1)
	{
		t.x += 10;
		t.y += 10;
		t2.x -= 20;
		t2.y -= 20;
		draw_square(contr, t, t2, 0x00000000);
	}
}

void	draw_hp(t_contr *contr)
{
	t_vpi	t;
	t_vpi	t2;

	t.y = contr->res.y - 100;
	t.x = 10;
	t2.x = 0.25 * 1000;
	t2.y = 40;
	draw_square_i(contr, t, t2, 0x00000000);
	t2.x = 0.25 * contr->hp;
	if (contr->hp > 750)
		draw_square_i(contr, t, t2, 0x0000FF00);
	else if (contr->hp > 500)
		draw_square_i(contr, t, t2, 0x00FFFF00);
	else if (contr->hp > 250)
		draw_square_i(contr, t, t2, 0x00FFA500);
	else
		draw_square_i(contr, t, t2, 0x00FF0000);
	if (contr->hp == 0)
		close_(contr, 0);
}

void	init_width(t_contr *contr, t_vpi *width)
{
	width[0].x = (contr->mpd.x > contr->mpd.y) ? contr->res.y / contr->mpd.x /
		5 : contr->res.x / contr->mpd.y / 5;
	width[0].y = (contr->mpd.x > contr->mpd.y) ? contr->res.y / contr->mpd.x /
		5 : contr->res.x / contr->mpd.y / 5;
	width[1] = set_vpi(width[0].x / 2, width[0].y / 2);
}

void	draw_minmap(t_contr *contr)
{
	t_vpi draw_p;
	t_vpi p;
	t_vpi width[2];

	p = set_vpi(-1, -1);
	draw_p = set_vpi(0, 0);
	init_width(contr, width);
	while (++p.y < contr->mpd.y)
	{
		p.x = -1;
		draw_p.x = 0;
		while (++p.x < contr->mpd.x)
		{
			if (contr->map[p.y][p.x] == '1')
				draw_square_i(contr, draw_p, width[0], 0x00FFFFFF);
			else if (contr->map[p.y][p.x] == '2')
				draw_square_i(contr, draw_p, width[1], 0x0000FF00);
			draw_p.x += width[0].x;
		}
		draw_p.y += width[0].y;
	}
	draw_p = set_vpi((contr->pos.x - 0.25) * width[0].x, (contr->pos.y - 0.25)
		* width[0].y);
	width[0] = set_vpi(width[0].x * 0.5, width[0].y * 0.5);
	draw_square_i(contr, draw_p, width[0], 0x00FF0000);
}
