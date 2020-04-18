/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:24:45 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 06:55:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int			hit_wall(t_contr *contr, t_col_rend *r, t_vpi *map)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
	{
		side = (r->side_dist.x < r->side_dist.y) ? 0 : 1;
		if (r->side_dist.y > r->side_dist.x && (map->x += r->step.x))
			r->side_dist.x += r->delta_dist.x;
		else if (map->y += r->step.y)
			r->side_dist.y += r->delta_dist.y;
		if (contr->map[map->y][map->x] == '1')
			hit = 1;
	}
	return (side);
}

int			get_tx_id(int side, t_vpi step)
{
	if (side == 1 && step.y > 0)
		return (1);
	else if (side == 1 && step.y < 0)
		return (0);
	else if (side == 0 && step.x > 0)
		return (3);
	else
		return (2);
}

void		init_r(t_contr *contr, t_col_rend *r)
{
	r->pos = contr->pos;
	r->dir = contr->dir;
	r->plane = contr->plane;
}

t_col_rend	draw_bcb(t_contr *contr)
{
	t_col_rend r;

	init_r(contr, &r);
	draw_floor(contr);
	return (r);
}

t_col_rend	draw_bc(t_contr *contr)
{
	t_col_rend r;

	init_r(contr, &r);
	drawback(contr);
	return (r);
}
