/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:57:52 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 19:29:15 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	move_spr(t_contr *contr)
{
	t_vp dist;

	if (contr->enn_id == -1)
		return ;
	contr->sprites[contr->enn_id].y += (contr->pos.y -
		contr->sprites[contr->enn_id].y) / 180;
	contr->sprites[contr->enn_id].x += (contr->pos.x -
		contr->sprites[contr->enn_id].x) / 180;
	contr->sprites[contr->enn_id].texture = contr->textures[contr->tx_nb - 2];
	dist.x = fabs(contr->pos.x - contr->sprites[contr->enn_id].x);
	dist.y = fabs(contr->pos.y - contr->sprites[contr->enn_id].y);
	if (dist.y < 0.75 && dist.x < 0.75)
		contr->hp -= 10;
}

void	draw_drk_b(t_contr *contr)
{
	t_vpi t;
	t_vpi t2;

	t.x = 250;
	t.y = 260;
	t2.x = 40;
	t2.y = 40;
	draw_square_i(contr, t, t2, 0x00FFFFFF);
	if (contr->dark_mode == 1)
	{
		t.x += 10;
		t.y += 10;
		t2.x -= 20;
		t2.y -= 20;
		draw_square_i(contr, t, t2, 0x00000000);
	}
}

void	show_sett(t_contr *contr)
{
	t_vpi	xy;
	t_vpi	start;
	int		width;
	int		i;

	xy = set_vpi(0, 0);
	i = -1;
	start = set_vpi(70, 90);
	while ((xy.x = 0) || ++i < 3)
	{
		width = contr->sett.rot_speed * 23;
		if (i == 0)
			width = contr->sett.fov * 23;
		else if (i == 1)
			width = contr->sett.move_speed * 23;
		while (++xy.x < width)
		{
			xy.y = -1;
			while (xy.y++ < 20)
				mlx_pixel_put(contr->mlx, contr->win_ptr, start.x + xy.x,
					start.y + xy.y, 0x00FFFFFF);
		}
		start.y += 60;
	}
	draw_drk_b(contr);
}

void	print_menu(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	(contr->textures[8]).texture.img, x, y);
	show_sett(contr);
	mlx_destroy_image(contr->mlx, contr->img.img);
	contr->img.img = mlx_new_image(contr->mlx, contr->res.x, contr->res.y);
	contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp),
		&(contr->img.length), &(contr->img.endian));
}

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
