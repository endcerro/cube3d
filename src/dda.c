#include "../header/header.h"

void draw_col(int col, int start, int end, int color, t_contr *contr)
{

	int floor;
	int ceil;
	int i;

	floor = 0x0000FF00;
	ceil = 0x000000FF;
	i = -1;
	while(++i < contr->res_h)
	{
		if(i < start)
			p_px(contr, col, i, floor);
		else if(i > end)
			p_px(contr, col, i, ceil);
		else
			p_px(contr, col, i, color);
	}
}

void dda(t_contr *contr)
{
	int 	x;
	t_vp	pos; 
	t_vp	dir;
	t_vp	plane;

	pos = contr->pos;
	dir = contr->dir;
	plane = contr->plane;

	x = -1;
	while(++x < contr->res_w)
	{
		double cameraX = 2 * x / (double)contr->res_w - 1;
		double rayDirX = dir.x + plane.x * cameraX;
		double rayDirY = dir.y + plane.y * cameraX;

	  //which box of the map we're in
		int mapX = (int)pos.x;
		int mapY = (int)pos.y;

	  	//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

	   	//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

	  	//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (pos.x - mapX) * deltaDistX;
	  	}
	  	else
	 	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
		}
		while (hit == 0)
      	{
        //jump to next map square, OR in x-direction, OR in y-direction
        	if (sideDistX < sideDistY)
        	{
          		sideDistX += deltaDistX;
        	  	mapX += stepX;
         	 	side = 0;
        	}
        	else
        	{	
          		sideDistY += deltaDistY;
          		mapY += stepY;
          		side = 1;
        	}
        	//Check if ray has hit a wall
        	if (contr->map[mapX][mapY] > 0)
        		hit = 1;
      	}
      	if(side == 0)
      		perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
      	else
      		perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY; 
	
      	int lineHeight = (int)(contr->res_h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      	int drawStart = -lineHeight / 2 + contr->res_h / 2;
      	int drawEnd = lineHeight / 2 + contr->res_h / 2;

      	if(drawStart < 0)
      		drawStart = 0;
      	if(drawEnd >= contr->res_h)
      		drawEnd = contr->res_h - 1;

      	draw_col(x, drawStart, drawEnd, 0x00FF0000, contr);
	}
}





























































