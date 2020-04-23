/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:30:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/23 17:19:23 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int		check_move(int y, int x, t_contr *contr)
{
	if (contr->map[y][x] != '2' && contr->map[y][x] != '1' &&
		contr->map[y][x] != 0)
		return (1);
	return (0);
}

int		check_fw_bw(t_contr *contr, char c, double move_speed)
{
	int ret;

	ret = 0;
	if (c == 1)
	{
		if (check_move((int)(contr->pos.y),
			(int)(contr->pos.x + contr->dir.x * move_speed), contr))
			ret++;
		if (check_move((int)(contr->pos.y + contr->dir.y * move_speed),
			(int)(contr->pos.x), contr))
			ret += 2;
	}
	else if (c == -1)
	{
		if (check_move((int)contr->pos.y,
			(int)(contr->pos.x - contr->dir.x * move_speed), contr))
			ret++;
		if (check_move((int)(contr->pos.y - contr->dir.y * move_speed),
			(int)(contr->pos.x), contr))
			ret += 2;
	}
	return (ret);
}

int		check_str_(t_contr *contr, double move_speed, int dir)
{
	int ret;

	ret = 0;
	if (dir == 1)
	{
		if (check_move((int)contr->pos.y,
			(int)(contr->pos.x + contr->plane.x * move_speed), contr))
			ret++;
		if (check_move((int)(contr->pos.y + contr->plane.y * move_speed),
			(int)contr->pos.x, contr))
			ret += 2;
	}
	else if (dir == -1)
	{
		if (check_move((int)contr->pos.y,
			(int)(contr->pos.x - contr->plane.x * move_speed), contr))
			ret++;
		if (check_move((int)(contr->pos.y - contr->plane.y * move_speed),
			(int)contr->pos.x, contr))
			ret += 2;
	}
	return (ret);
}

void	rotate(t_contr *contr, int dir, double rot_speed)
{
	t_vp old;

	old.x = contr->dir.x;
	old.y = contr->plane.x;
	contr->dir.x = contr->dir.x * cos(dir * rot_speed) -
		contr->dir.y * sin(dir * rot_speed);
	contr->dir.y = old.x * sin(dir * rot_speed) +
		contr->dir.y * cos(-rot_speed);
	contr->plane.x = contr->plane.x * cos(dir * rot_speed) -
		contr->plane.y * sin(dir * rot_speed);
	contr->plane.y = old.y * sin(dir * rot_speed) +
		contr->plane.y * cos(dir * rot_speed);
}
