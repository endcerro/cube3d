/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/12 15:23:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void		draw_col(t_contr *contr, t_col_rend *r)
{
	int		color_t;
	int		y;

	y = r->draw_v.x - 1;
	while (++y < r->draw_v.y)
	{
		r->tex_m.y += r->tx_step;
		color_t = g_px(contr->textures[r->tx_id], r->tex_m.x, r->tex_m.y);
		if (contr->dark_mode == 1)
			color_t = dark_mode_mod(color_t, r->perp_w_dst);
		p_px(contr, r->x, y, color_t);
	}
}

void		get_side_dist(t_contr *contr, t_col_rend *r)
{
	//DIR IS EACH VECTOR OF THE CAMERA PLANE (NORM / RES)
	r->ray_dir.x = r->dir.x + r->plane.x *
		(2 * r->x / (double)contr->res.x - 1);
	r->ray_dir.y = r->dir.y + r->plane.y *
		(2 * r->x / (double)contr->res.x - 1);
	r->map.x = (int)r->pos.x;
	r->map.y = (int)r->pos.y;
	//PYTHAGORE SIMPLIFICATION TO GET THE DISTANCE FROM ONE MAP BOX TO ANOTHER
	r->delta_dist.x = fabs(1 / r->ray_dir.x);
	r->delta_dist.y = fabs(1 / r->ray_dir.y);
	// if(r->x == contr->res.x / 2)// && r->x <= contr->res.x / 2 + 5)
		// printf("r:%d dx = %f dy = %f\n",r->x, r->side_dist.x, r->side_dist.y );
	//DIR OF THE RAYS
	r->step.y = (r->ray_dir.y < 0) ? -1 : 1;
	r->step.x = (r->ray_dir.x < 0) ? -1 : 1;
	//GET DISTANCE TO MAP BOX  
	r->side_dist.x = (r->ray_dir.x < 0) ? (r->pos.x - r->map.x)
		* r->delta_dist.x :
		(r->map.x + 1.0 - r->pos.x) * r->delta_dist.x;
	r->side_dist.y = (r->ray_dir.y < 0) ? (r->pos.y - r->map.y)
		* r->delta_dist.y :
		(r->map.y + 1.0 - r->pos.y) * r->delta_dist.y;
		// if(r->x == contr->res.x / 2)// && r->x <= contr->res.x / 2 + 5)
		// 	printf("r:%d sdx = %f sdy = %f\n",r->x, r->side_dist.x, r->side_dist.y );
}

void		pre_draw(t_contr *contr, t_col_rend *r)
{
	//GET DISTANCE TO CLOSEST WALL BY DIVIDING THE HITTING PART OF THE RAY 
	double crossed;

	crossed = (r->side == 0) ? (r->map.x - r->pos.x + (1 - r->step.x) / 2) : 
		(r->map.y - r->pos.y + (1 - r->step.y) / 2);
	//DIVIDE BY THE VECT TO GET REAL DIST
	r->perp_w_dst = (r->side == 0) ? crossed / r->ray_dir.x : 
		crossed / r->ray_dir.y;
	r->perp_w_dst = (r->perp_w_dst == 0) ? 0.1 : r->perp_w_dst;
	r->line_h = (int)(contr->res.y / r->perp_w_dst);
	//VERIFICATION OF THE DRAWING COORDS
	r->draw_v.x = (-r->line_h / 2 + contr->res.y / 2 < 0) ? 0 :
		-r->line_h / 2 + contr->res.y / 2;
	r->draw_v.y = (r->line_h / 2 + contr->res.y / 2 > contr->res.y) ?
		contr->res.y : (r->line_h / 2 + contr->res.y / 2);
	//GET DECIMAL OF THE HIT WALL
	r->wall_x = (r->side == 0) ? r->pos.y + r->perp_w_dst * r->ray_dir.y :
		r->pos.x + r->perp_w_dst * r->ray_dir.x;
	r->wall_x -= floor(r->wall_x);
	r->tex_m.x = contr->textures[r->tx_id].w -
		(int)(r->wall_x * (double)contr->textures[r->tx_id].w); //- 1;
	r->tx_step = 1.0 * contr->textures[r->tx_id].w / r->line_h;
	//STARTING PIXEL (TOP OF THE COLMN)
	r->tex_m.y = (r->draw_v.x - contr->res.y / 2 + r->line_h / 2) *
		r->tx_step - r->tx_step;
}

void		wall_cast(t_contr *contr)
{
	t_col_rend	r;
	double		z_buffer[contr->res.x];

	r = draw_bc(contr);
	r.z_buffer = z_buffer;
	r.x = -1;
	while (++r.x < contr->res.x)
	{
		get_side_dist(contr, &r);
		r.side = hit_wall(contr, &r, &r.map);
		r.tx_id = get_tx_id(r.side, r.step);
		pre_draw(contr, &r);
		draw_col(contr, &r);
		r.z_buffer[r.x] = r.perp_w_dst;
	}
	spritecast(contr, r.z_buffer);
}
