/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:27:55 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 19:29:40 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	respawn_enn(t_contr *contr)
{
	if (contr->enn_id == -1)
		return ;
	contr->sprites[contr->enn_id].x = (double)get_rdm(0, contr->mpd.x);
	contr->sprites[contr->enn_id].y = (double)get_rdm(0, contr->mpd.y);
}

int		get_rdm(int lower, int upper)
{
	return ((rand() % (upper - lower + 1)) + lower);
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
