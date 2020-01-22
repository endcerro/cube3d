/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 07:23:43 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void draw_col(int col, int start, int end, int color, t_contr *contr)
{

	int floor;
	int ceil;
	int i;

	floor = 0x0000FF00;
	ceil = 0x000000FF;
	i = start - 1;

	while (++i < end)
		p_px(contr, col, i, color);
	
	// while(++i < contr->res_h)
	// {
	// 	if(i < start)
	// 		p_px(contr, col, i, floor);
	// 	else if(i > end)
	// 		p_px(contr, col, i, ceil);
	// 	else
	// 		p_px(contr, col, i, color);
	// }
}
void	drawback(t_contr* contr)
{
	int floor;
	int ceil;
	int i;

	floor = 0x696969;
	ceil = 0x808080;
	int j;

	i = -1;
	while(++i < contr->res_h / 2)
	{
		j = -1;
		while(++j < contr->res_w)
			p_px(contr, j, i, ceil);
	}
	while(++i < contr->res_h)
	{
		j = -1;
		while(++j < contr->res_w)
			p_px(contr, j, i, floor);
	}

	// printf("out\n");
}
void dda(t_contr *contr)
{
	// printf("ici\n");
	
	int 	x;
	t_vp	pos; 
	t_vp	dir;
	t_vp	plane;

	pos = contr->pos;
	dir = contr->dir;
	plane = contr->plane;

	drawback(contr);
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


      	int color = 0x484848;

      // switch(worldMap[mapX][mapY])
      // {
      //   case 1:  color = RGB_Red;  break; //red
      //   case 2:  color = RGB_Green;  break; //green
      //   case 3:  color = RGB_Blue;   break; //blue
      //   case 4:  color = RGB_White;  break; //white
      //   default: color = RGB_Yellow; break; //yellow
      // }

      //give x and y sides different brightness
      if (side == 1)
      	color = 0x282828;


      	draw_col(x, drawStart, drawEnd, color, contr);
	}
}





