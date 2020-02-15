/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:30:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/15 20:47:22 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int		check_fw_bw(t_contr *contr, char c, double move_speed)
{
	int ret;

	ret = 0;
	if (c == 1)
	{
		if (contr->map[(int)(contr->pos.x + contr->dir.x * move_speed)]
			[(int)contr->pos.y] == '0')
			ret++;
		if (contr->map[(int)contr->pos.x]
			[(int)(contr->pos.y + contr->dir.y * move_speed)] == '0')
			ret += 2;
	}
	else if (c == -1)
	{
		if (contr->map[(int)(contr->pos.x - contr->dir.x * move_speed)]
		[(int)contr->pos.y] == '0')
			ret++;
		if (contr->map[(int)(contr->pos.x)]
			[(int)(contr->pos.y - contr->dir.y * move_speed)] == '0')
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
		if (contr->map[(int)(contr->pos.x + contr->plane.x * move_speed)]
			[(int)contr->pos.y] == '0')
			ret++;
		if (contr->map[(int)contr->pos.x]
			[(int)(contr->pos.y + contr->plane.y * move_speed)] == '0')
			ret += 2;
	}
	else if (dir == -1)
	{
		if (contr->map[(int)(contr->pos.x - contr->plane.x * move_speed)]
			[(int)contr->pos.y] == '0')
			ret++;
		if (contr->map[(int)(contr->pos.x)]
			[(int)(contr->pos.y - contr->plane.y * move_speed)] == '0')
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
