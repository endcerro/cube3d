/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:33:56 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 23:35:12 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void handle_keys(t_contr *contr)
{
	double move_speed;
	double rot_speed;
	// printf("aaa\n" );
	rot_speed = M_PI / 90;
	move_speed = 0.25;
	double oldx;
	double oldpx;
	// printf("%s\n", );
	if (contr->key.w != 0 )
	{ //W
		if(contr->map[(int)(contr->pos.x + contr->dir.x * move_speed)][(int)contr->pos.y] == 0)
			contr->pos.x += contr->dir.x * move_speed;
		if(contr->map[(int)contr->pos.x][(int)(contr->pos.y + contr->dir.y * move_speed)] == 0)
			contr->pos.y += contr->dir.y * move_speed;
	}
	if (contr->key.s != 0) //s
	{
		if(contr->map[(int)(contr->pos.x - contr->dir.x * move_speed)][(int)contr->pos.y] == 0)
			contr->pos.x -= contr->dir.x * move_speed;
		if(contr->map[(int)(contr->pos.x)][(int)(contr->pos.y - contr->dir.y * move_speed)] == 0)
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
	if (contr->key.e != 0)
	{
		if(contr->map[(int)(contr->pos.x + contr->plane.x * move_speed)][(int)contr->pos.y] == 0)
			contr->pos.x += contr->plane.x * move_speed;
		if(contr->map[(int)contr->pos.x][(int)(contr->pos.y + contr->plane.y * move_speed)] == 0)
			contr->pos.y += contr->plane.y * move_speed;
	}
	if (contr->key.q != 0)
	{
		if(contr->map[(int)(contr->pos.x - contr->plane.x * move_speed)][(int)contr->pos.y] == 0)
			contr->pos.x -= contr->plane.x * move_speed;
		if(contr->map[(int)(contr->pos.x)][(int)(contr->pos.y - contr->plane.y * move_speed)] == 0)
			contr->pos.y -= contr->plane.y * move_speed;
	}
}


int key_press(int key, t_contr *contr)
{
	// 	printf("%d\n",key);
	if (key == 13)
		contr->key.w = 1;
	else if (key == 1) //s
		contr->key.s = 1;
	else if (key == 2)
		contr->key.e = 1;
	else if (key == 0) //D
		contr->key.q = 1;
	else if (key == 12) //Q
		contr->key.q = 1;
	else if (key == 14) //E
		contr->key.e = 1;
	else if (key==82)
		contr->dark_mode = !contr->dark_mode;
	else if (key==123) //gauche
	 	contr->key.d = 1;
	else if (key==124) //gauche
	 	contr->key.a = 1;
	if(key == 53)
		exit(0);
	return 0;
}

int key_release(int key, t_contr *contr)
{
	if (key == 13)
		contr->key.w = 0;
	else if (key == 1) //s
		contr->key.s = 0;
	else if (key == 2)
		contr->key.e = 0;
	else if (key == 0) //D
		contr->key.q = 0;
	else if (key == 12) //Q
		contr->key.q = 0;
	else if (key == 14) //E
		contr->key.e = 0;
	else if (key==123) //gauche
	 	contr->key.d = 0;
	else if (key==124) //gauche
	 	contr->key.a = 0;
	//printf("KEYUP = %d \n",key );
	return 0;
}
