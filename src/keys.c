#include "../header/header.h"

int key_press(int key, t_contr *param)
{
	double move_speed;
	double rot_speed;
	// printf("%d\n",key );
	contr = (t_contr*)param;
	rot_speed = M_PI/180;
	move_speed = 0.05;
	double oldx;
	double oldpx;
	//W13
	//A0
	//S1
	//D2
	if (key == 13)
	{ //W
		contr->pos.x += contr->dir.x * move_speed;
		contr->pos.y += contr->dir.y * move_speed;
	}
	else if (key == 1) //s
	{
		contr->pos.x -= contr->dir.x * move_speed;
		contr->pos.y -= contr->dir.y * move_speed;
	} 
	else if (key == 0)
	{
		double oldx = contr->dir.x;
      	contr->dir.x = contr->dir.x * cos(-rot_speed) - contr->dir.y * sin(-rot_speed);
      	contr->dir.y = oldx * sin(-rot_speed) + contr->dir.y * cos(-rot_speed);
      	oldpx = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(-rot_speed) - contr->plane.y * sin(-rot_speed);
      	contr->plane.y = oldpx * sin(-rot_speed) + contr->plane.y * cos(-rot_speed);
	} //A
	else if (key == 2) //D
	{
		oldx = contr->dir.x;
      	contr->dir.x = contr->dir.x * cos(rot_speed) - contr->dir.y * sin(rot_speed);
      	contr->dir.y = oldx * sin(rot_speed) + contr->dir.y * cos(rot_speed);
      	oldpx = contr->plane.x;
      	contr->plane.x = contr->plane.x * cos(rot_speed) - contr->plane.y * sin(rot_speed);
      	contr->plane.y = oldpx * sin(rot_speed) + contr->plane.y * cos(rot_speed);
	}
	else if(key == 125)
	{

	}
	else if(key == 126)
	{

	}
	else if(key == 12)
	{
		
	}
	else if(key == 14)
	{
		
	}

	if(key == 53)
		exit(0);

	return 0;
}

int key_release(int key, t_contr *param)
{
	//printf("KEYUP = %d \n",key );
	return 0;
}