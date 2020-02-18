/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/18 17:59:20 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void		draw_col(t_contr *contr, t_col_rend *r)
{
	int		color_t;
	int		y;
	float	val;
	t_color color;

	y = r->draw_v.x - 1;
	while (++y < r->draw_v.y)
	{
		r->tex_m.y += r->tx_step;
		color_t = g_px(contr->textures[r->tx_id], r->tex_m.x, r->tex_m.y);
		color.r = 0xff0000 & color_t;
		color.g = 0xff00 & color_t;
		color.b = 0xff & color_t;
		if (contr->dark_mode == 1)
		{
			val = (1.0f - r->perpWallDist / VIEW_DIST);
			val = (val < 0.0) ? 0.0f : val;
			val = (val > 1.0) ? 1.0f : val;
			color.r = ((int)((double)0x0 + (color.r - 0x0) * val) & 0xFF0000);
			color.g = ((int)((double)0x0 + (color.g - 0x0) * val) & 0xFF00);
			color.b = ((int)((double)0x0 + (color.b - 0x0) * val) & 0xFF);
		}
		p_px(contr, r->x, y, color.r + color.g + color.b);
	}
}

void		get_side_dist(t_contr *contr, t_col_rend *r)
{
	r->ray_dir.x = r->dir.x + r->plane.x *
		(2 * r->x / (double)contr->res_w - 1);
	r->ray_dir.y = r->dir.y + r->plane.y *
		(2 * r->x / (double)contr->res_w - 1);
	r->map.x = (int)r->pos.x;
	r->map.y = (int)r->pos.y;
	r->delta_dist.x = fabs(1 / r->ray_dir.x);
	r->delta_dist.y = fabs(1 / r->ray_dir.y);
	r->step.y = (r->ray_dir.y < 0) ? -1 : 1;
	r->step.x = (r->ray_dir.x < 0) ? -1 : 1;
	r->side_dist.x = (r->ray_dir.x < 0) ? (r->pos.x - r->map.x)
		* r->delta_dist.x :
		(r->map.x + 1.0 - r->pos.x) * r->delta_dist.x;
	r->side_dist.y = (r->ray_dir.y < 0) ? (r->pos.y - r->map.y)
		* r->delta_dist.y :
		(r->map.y + 1.0 - r->pos.y) * r->delta_dist.y;
}

void		pre_draw(t_contr *contr, t_col_rend *r)
{
	r->perpWallDist = (r->side == 0) ? (r->map.x - r->pos.x +
		(1 - r->step.x) / 2) / r->ray_dir.x :
			(r->map.y - r->pos.y + (1 - r->step.y) / 2) / r->ray_dir.y;
	r->lineHeight = (int)(contr->res_h / r->perpWallDist);
	r->draw_v.x = (-r->lineHeight / 2 + contr->res_h / 2 < 0) ? 0 :
		-r->lineHeight / 2 + contr->res_h / 2;
	r->draw_v.y = (r->lineHeight / 2 + contr->res_h / 2 > contr->res_h) ?
		contr->res_h : (r->lineHeight / 2 + contr->res_h / 2);
	r->wallX = (r->side == 0) ? r->pos.y + r->perpWallDist * r->ray_dir.y :
		r->pos.x + r->perpWallDist * r->ray_dir.x;
	r->wallX -= floor(r->wallX);
	r->tex_m.x = contr->textures[r->tx_id].w -
		(int)(r->wallX * (double)contr->textures[r->tx_id].w) - 1;
	r->tx_step = 1.0 * contr->textures[r->tx_id].w / r->lineHeight;
	r->tex_m.y = (r->draw_v.x - contr->res_h / 2 + r->lineHeight / 2) *
		r->tx_step - r->tx_step;
}

void		dda(t_contr *contr)
{
	t_col_rend	r;
	double		z_buffer[contr->res_w];

	r = draw_bc(contr);
	r.z_buffer = z_buffer;
	r.x = -1;
	while (++r.x < contr->res_w)
	{
		get_side_dist(contr, &r);
		r.side = hit_wall(contr, &r, &r.map);
		r.tx_id = get_tx_id(r.side, r.step);
		pre_draw(contr, &r);
		draw_col(contr, &r);
		r.z_buffer[r.x] = r.perpWallDist;
	}
	spritecast(contr, r.z_buffer);
}
