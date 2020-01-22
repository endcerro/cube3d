/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:33:56 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 06:42:51 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void handle_keys(t_contr *contr)
{
	double move_speed;
	double rot_speed;
	// printf("aaa\n" );
	rot_speed = M_PI / 100;
	move_speed = 0.15;
	double oldx;
	double oldpx;

	if (contr->key.w != 0 )
	{ //W
		contr->pos.x += contr->dir.x * move_speed;
		contr->pos.y += contr->dir.y * move_speed;
	}
	if (contr->key.s != 0) //s
	{
		contr->pos.x -= contr->dir.x * move_speed;
		contr->pos.y -= contr->dir.y * move_speed;
	} 
	if (contr->key.a != 0)
	{
		oldx = contr->dir.x;
      	contr->dir.x = contr->dir.x * cos(-rot_speed) - contr->dir.y * sin(-rot_speed);
      	contr->dir.y = oldx * sin(-rot_speed) + contr->dir.y * cos(-rot_speed);
      	oldpx = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(-rot_speed) - contr->plane.y * sin(-rot_speed);
      	contr->plane.y = oldpx * sin(-rot_speed) + contr->plane.y * cos(-rot_speed);
	} //A
	if (contr->key.d != 0) //D
	{
		oldx = contr->dir.x;
      	contr->dir.x = contr->dir.x * cos(rot_speed) - contr->dir.y * sin(rot_speed);
      	contr->dir.y = oldx * sin(rot_speed) + contr->dir.y * cos(rot_speed);
      	oldpx = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(rot_speed) - contr->plane.y * sin(rot_speed);
      	contr->plane.y = oldpx * sin(rot_speed) + contr->plane.y * cos(rot_speed);
	}
}


int key_press(int key, t_contr *contr)
{
	// printf("ici\n");
	if (key == 13)
		contr->key.w = 1;
	else if (key == 1) //s
		contr->key.s = 1;
	else if (key == 2)
		contr->key.a = 1;
	else if (key == 0) //D
		contr->key.d = 1;
	if(key == 53)
		exit(0);
		// close_(contr);

	return 0;
}

int key_release(int key, t_contr *contr)
{
	if (key == 13)
		contr->key.w = 0;
	else if (key == 1) //s
		contr->key.s = 0;
	else if (key == 2)
		contr->key.a = 0;
	else if (key == 0) //D
		contr->key.d = 0;
	//printf("KEYUP = %d \n",key );
	return 0;
}
