/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 02:37:24 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 02:59:31 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int		get_rdm(int lower, int upper)
{
	return ((rand() % (upper - lower + 1)) + lower);
}

void	respawn_enn(t_contr *contr)
{
	if (contr->enn_id == -1)
		return ;
	contr->sprites[contr->enn_id].x = (double)get_rdm(0, contr->mpd.x);
	contr->sprites[contr->enn_id].y = (double)get_rdm(0, contr->mpd.y);
}

void	check_hit(t_contr *contr)
{
	t_vp dist;

	dist.x = fabs(contr->pos.x - contr->sprites[contr->enn_id].x);
	dist.y = fabs(contr->pos.y - contr->sprites[contr->enn_id].y);
	contr->atk_frame = 15;
	if (dist.x < 1.5 && dist.y < 1.5)
		respawn_enn(contr);
}

void	move_enn(t_contr *contr)
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
