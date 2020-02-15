/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:33:56 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/15 18:39:24 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int check_fw_bw(t_contr *contr, char c, double move_speed)
{
	int ret;

	ret = 0;
	if (c == 'f')
	{
		if(contr->map[(int)(contr->pos.x + contr->dir.x * move_speed)]
			[(int)contr->pos.y] == '0')
			ret++;
		if(contr->map[(int)contr->pos.x]
			[(int)(contr->pos.y + contr->dir.y * move_speed)] == '0')
			ret += 2;
	}
	else if (c == 'b')
	{
		if(contr->map[(int)(contr->pos.x - contr->dir.x * move_speed)]
		[(int)contr->pos.y] == '0')
			ret++;
		if(contr->map[(int)(contr->pos.x)]
			[(int)(contr->pos.y - contr->dir.y * move_speed)] == '0')
			ret += 2;
	}
	return ret;
}

void handle_keys(t_contr *contr)
{
	double move_speed;
	double rot_speed;
	int cache;
	t_vp old;

	rot_speed = M_PI / 90;
	move_speed = 0.25;
	if (contr->key.w != 0)
	{ 
		cache = check_fw_bw(contr, 'f', move_speed);
		if(cache == 1 || cache == 3)
			contr->pos.x += contr->dir.x * move_speed;
		if(cache >= 2)
			contr->pos.y += contr->dir.y * move_speed;
	}
	if (contr->key.s != 0)
	{
		cache = check_fw_bw(contr, 'b', move_speed);
		if(cache == 1 || cache == 3)
			contr->pos.x -= contr->dir.x * move_speed;
		if(cache >= 2)
			contr->pos.y -= contr->dir.y * move_speed;
	}
	if (contr->key.a != 0)
	{
		old.x = contr->dir.x; 
		contr->dir.x = contr->dir.x * cos(-rot_speed) - contr->dir.y * sin(-rot_speed);
      	contr->dir.y = old.x * sin(-rot_speed) + contr->dir.y * cos(-rot_speed);
      	old.y = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(-rot_speed) - contr->plane.y * sin(-rot_speed);
      	contr->plane.y = old.y * sin(-rot_speed) + contr->plane.y * cos(-rot_speed);
	} //A
	if (contr->key.d != 0) //D
	{
		old.x = contr->dir.x; 
		contr->dir.x = contr->dir.x * cos(rot_speed) - contr->dir.y * sin(rot_speed);
      	contr->dir.y = old.x * sin(rot_speed) + contr->dir.y * cos(rot_speed);
      	old.y = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(rot_speed) - contr->plane.y * sin(rot_speed);
      	contr->plane.y = old.y * sin(rot_speed) + contr->plane.y * cos(rot_speed);
	}
	if (contr->key.e != 0)
	{
		if(contr->map[(int)(contr->pos.x + contr->plane.x * move_speed)][(int)contr->pos.y] == '0')
			contr->pos.x += contr->plane.x * move_speed;
		if(contr->map[(int)contr->pos.x][(int)(contr->pos.y + contr->plane.y * move_speed)] == '0')
			contr->pos.y += contr->plane.y * move_speed;
	}
	if (contr->key.q != 0)
	{
		if(contr->map[(int)(contr->pos.x - contr->plane.x * move_speed)][(int)contr->pos.y] == '0')
			contr->pos.x -= contr->plane.x * move_speed;
		if(contr->map[(int)(contr->pos.x)][(int)(contr->pos.y - contr->plane.y * move_speed)] == '0')
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
		close_(contr, 0);
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
