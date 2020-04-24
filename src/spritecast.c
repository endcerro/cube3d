/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:23:38 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/23 16:57:19 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	prep_sprites(t_contr *contr, t_sprite_rend *r)
{
	int i;

	i = -1;
	while (++i < contr->sprites_nb)
	{
		r->spr_ord[i] = i;
		r->spr_dst[i] = ((contr->pos.x - contr->sprites[i].x) *
			(contr->pos.x - contr->sprites[i].x) +
			(contr->pos.y - contr->sprites[i].y) *
			(contr->pos.y - contr->sprites[i].y));
	}
}

void	correct_dse(t_contr *contr, t_sprite_rend *r)
{
	t_vpi cache;

	cache.x = -r->sprite_d.y / 2 + contr->res.y / 2;
	r->draw_start.y = (cache.x < 0) ? 0 : cache.x;
	cache.x = r->sprite_d.y / 2 + contr->res.y / 2;
	r->draw_end.y = (cache.x >= contr->res.y) ? contr->res.y : cache.x;
	cache.x = -r->sprite_d.x / 2 + r->spr_screen_x;
	r->draw_start.x = (cache.x >= 0) ? cache.x : 0;
	cache.x = r->sprite_d.x / 2 + r->spr_screen_x;
	r->draw_end.x = (cache.x >= contr->res.x) ? contr->res.x : cache.x;
}

void	get_draw_s_e(t_contr *contr, t_sprite_rend *r, int i)
{
	double inverter;

	inverter = 1.0 /
		(contr->plane.x * contr->dir.y - contr->dir.x * contr->plane.y);
	r->sprite.x = contr->sprites[r->spr_ord[i]].x - contr->pos.x;
	r->sprite.y = contr->sprites[r->spr_ord[i]].y - contr->pos.y;
	r->transform.x = inverter * (contr->dir.y * r->sprite.x - contr->dir.x *
		r->sprite.y);
	r->transform.y = inverter * (-contr->plane.y * r->sprite.x + contr->plane.x
		* r->sprite.y);
	r->spr_screen_x = (int)((contr->res.x / 2) * (1 + r->transform.x /
		r->transform.y));
	r->sprite_d.y = abs((int)(contr->res.y / r->transform.y));
	r->sprite_d.x = abs((int)(contr->res.y / r->transform.y));
	correct_dse(contr, r);
}

void	draw_stripe(t_contr *contr, t_sprite_rend *r, int stripe, int i)
{
	int	color;
	int y;
	int	cache;

	y = r->draw_start.y - 1;
	r->tex_p.x = (int)((stripe - (-r->sprite_d.x / 2 + r->spr_screen_x))
	* r->sprites[i].texture.w / r->sprite_d.x);
	if (r->transform.y > 0 && stripe >= 0 && stripe < contr->res.x &&
		r->transform.y < r->z_buff[stripe])
		while (++y < r->draw_end.y)
		{
			cache = y * 2 - contr->res.y + r->sprite_d.y;
			r->tex_p.y = (cache * r->sprites[r->spr_ord[i]].texture.h) /
				r->sprite_d.y / 2;
			color = g_vpx(r->sprites[r->spr_ord[i]].texture, r->tex_p);
			if ((color & 0x00FFFFFF) != 0)
			{
				if (contr->dark_mode == 1)
					color = dark_mode_mod(color,
					r->spr_dst[r->spr_ord[i]] / (6 * vp_norm(contr->dir)));
				p_px(contr, stripe, y, color);
			}
		}
}

void	spritecast(t_contr *contr, double *z_buff)
{
	t_sprite_rend	r;
	int				i;
	int				spr_o[contr->sprites_nb];
	double			spr_d[contr->sprites_nb];
	int				col;

	r.sprites = contr->sprites;
	r.spr_ord = spr_o;
	r.spr_dst = spr_d;
	r.z_buff = z_buff;
	prep_sprites(contr, &r);
	sort_sprites(r.spr_dst, r.spr_ord, contr->sprites_nb);
	i = -1;
	while (++i < contr->sprites_nb)
	{
		get_draw_s_e(contr, &r, i);
		col = r.draw_start.x;
		while (col < r.draw_end.x)
			draw_stripe(contr, &r, col++, i);
	}
}
