/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:23:48 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/14 15:12:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	game_settings(int x, int y, t_contr *contr)
{
	if (x >= 325 && x <= 345)
	{
		if (y >= 90 && y <= 110 && contr->sett.fov < 10)
			change_fov(contr, -1);
		else if (y >= 150 && y <= 170 && contr->sett.move_speed < 10)
			contr->sett.move_speed++;
		else if (y >= 210 && y <= 230 && contr->sett.rot_speed < 10)
			contr->sett.rot_speed++;
	}
	else if (x >= 30 && x <= 50)
	{
		if (y >= 90 && y <= 110 && contr->sett.fov > 1)
			change_fov(contr, 1);
		else if (y >= 150 && y <= 170 && contr->sett.move_speed > 1)
			contr->sett.move_speed--;
		else if (y >= 210 && y <= 230 && contr->sett.rot_speed > 1)
			contr->sett.rot_speed--;
	}
}

int		mouse_(int btn, int x, int y, t_contr *contr)
{
	int		ring;

	ring = 1;
	btn = 0;
	if (!contr->menu_mode)
		return (0);
	game_settings(x, y, contr);
	if (y >= 355 && y <= 385)
	{
		if (x >= 35 && x <= 115)
			contr->menu_mode = 0;
		else if (x >= 289 && x <= 358 && (ring = 1))
			close_(contr, 0);
	}
	else if (y >= 260 && y <= 300)
		if (x >= 250 && x <= 290 && (ring = 1))
			contr->dark_mode = !contr->dark_mode;
	if (ring)
		btn = write(1, "\a", 1);
	return (btn);
}
