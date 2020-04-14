/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:33:56 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/14 16:12:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	handle_keys_n(t_contr *contr, double move_speed)
{
	int		cache;

	if (contr->key.e != 0 && (cache = check_str_(contr, move_speed, 1)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x += contr->plane.x * move_speed;
		if (cache >= 2)
			contr->pos.y += contr->plane.y * move_speed;
	}
	if (contr->key.q != 0 && (cache = check_str_(contr, move_speed, -1)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x -= contr->plane.x * move_speed;
		if (cache >= 2)
			contr->pos.y -= contr->plane.y * move_speed;
	}
}

void	handle_keys(t_contr *contr)
{
	double	move_speed;
	double	rot_speed;
	int		cache;

	rot_speed = (M_PI / 60) / 10 * contr->sett.rot_speed;
	move_speed = 0.025 * contr->sett.move_speed;
	if (contr->key.w != 0 && (cache = check_fw_bw(contr, 1, move_speed)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x += contr->dir.x * move_speed;
		if (cache >= 2)
			contr->pos.y += contr->dir.y * move_speed;
	}
	if (contr->key.s != 0 && (cache = check_fw_bw(contr, -1, move_speed)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x -= contr->dir.x * move_speed;
		if (cache >= 2)
			contr->pos.y -= contr->dir.y * move_speed;
	}
	if (contr->key.a != 0)
		rotate(contr, 1, rot_speed);
	if (contr->key.d != 0)
		rotate(contr, -1, rot_speed);
	handle_keys_n(contr, move_speed);
}

int		key_press(int key, t_contr *contr)
{
	if (key == 122)
		contr->key.w = 1;
	else if (key == 115)
		contr->key.s = 1;
	else if (key == 100)
		contr->key.e = 1;
	else if (key == 113)
		contr->key.q = 1;
	else if (key == 65361)
		contr->key.d = 1;
	else if (key == 65363)
		contr->key.a = 1;
	if (key == 65307)
		close_(contr, 0);
	if (key == 65289)
		contr->menu_mode = 1;
	if (key == 32)
		check_hit(contr);
	return (0);
}

int		key_release(int key, t_contr *contr)
{
	if (key == 122)
		contr->key.w = 0;
	else if (key == 115)
		contr->key.s = 0;
	else if (key == 100)
		contr->key.e = 0;
	else if (key == 113)
		contr->key.q = 0;
	else if (key == 65361)
		contr->key.d = 0;
	else if (key == 65363)
		contr->key.a = 0;
	return (0);
}
