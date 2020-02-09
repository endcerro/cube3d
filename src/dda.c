/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/09 18:26:35 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"


#define VIEW_DIST 8

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
}
void	drawback(t_contr* contr)
{
	int floor;
	int ceil;
	int i;

	floor = contr->f_color;
	ceil = contr->c_color;
	if(contr->dark_mode == 1)
	{
		floor = 0x0;
		ceil = 0x0;
	}
	int j;

	i = -1;
	while(++i < contr->res_h / 2)
	{
		j = -1;
		while(++j < contr->res_w)
		{
			int color;
        	color = ceil;
			int R, G, B;
 			R = 0xff0000 & color;
 			G = 0xff00 & color;
 			B = 0xff & color;
 			if(contr->dark_mode == 1 )
 			{
 				float cur = contr->res_h / (2.0f * j - contr->res_h);
 				float yo = 1.0f - cur / VIEW_DIST;
 				if (yo < 0.0f)
 					yo = 0.0f;
 				else if (yo > 1.0f)
 					yo =  1.0f;
 				R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 				G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 				B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);
 			}
        	// p_px(contr, x, y, R + G + B);
			p_px(contr, j, i, R + G + B);
		}
	}
	while(++i < contr->res_h)
	{
		j = -1;
		while(++j < contr->res_w)
		{
			int color;
        	color = floor;
			int R, G, B;
 			R = 0xff0000 & color;
 			G = 0xff00 & color;
 			B = 0xff & color;
 			if(contr->dark_mode == 1 )
 			{
 				float cur = contr->res_h / (2.0f * j - contr->res_h);
 				float yo = 1.0f - cur / VIEW_DIST;
 				if (yo < 0.0f)
 					yo = 0.0f;
 				else if (yo > 1.0f)
 					yo =  1.0f;
 				R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 				G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 				B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);
 			}
        	// p_px(contr, x, y, R + G + B);
			p_px(contr, j, i, R + G + B);
		}
	}
}


void	draw_floor(t_contr *contr)
{
	t_vp dir;
	t_vp plane;
	t_vp pos;

	pos = contr->pos;
	dir = contr->dir;
	plane = contr->plane;
	for(int y = 0; y < contr->res_h; y++)
	{
	      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
  		float rayDirX0 = dir.x - plane.x;
      	float rayDirY0 = dir.y - plane.y;
      	float rayDirX1 = dir.x + plane.x;
      	float rayDirY1 = dir.y + plane.y;

	    
      	int p = y - contr->res_h / 2;
		float posZ = 0.5 * contr->res_h;
	  	float rowDistance = posZ / p;
	  	float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / contr->res_w;
      	float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / contr->res_w;
	  	float floorX = pos.x + rowDistance * rayDirX0;
      	float floorY = pos.y + rowDistance * rayDirY0;
      	for(int x = 0; x < contr->res_w; ++x)
      	{
	    	int cellX = (int)floorX;
        	int cellY = (int)floorY;
        	int tx = (int)(contr->textures[3 + 2].w * (floorX - cellX)) & (contr->textures[3 + 2].w - 1);
        	int ty = (int)(contr->textures[3 + 2].h * (floorY - cellY)) & (contr->textures[3 + 2].h - 1);

        	floorX += floorStepX;
        	floorY += floorStepY;

        	int color;
        	color = g_px(contr->textures[3 + 3], tx,ty);
			int R, G, B;
 			R = 0xff0000 & color;
 			G = 0xff00 & color;
 			B = 0xff & color;
 			if(contr->dark_mode == 1 )
 			{
 				float cur = contr->res_h / (2.0f * y - contr->res_h);
 				float yo = 1.0f - cur / VIEW_DIST;
 				if (yo < 0.0f)
 					yo = 0.0f;
 				else if (yo > 1.0f)
 					yo =  1.0f;
 				R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 				G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 				B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);
 			}
 			p_px(contr, x, y, R + G + B);
        	color = g_px(contr->textures[3 + 2], tx,ty);
			R = 0xff0000 & color;
 			G = 0xff00 & color;
 			B = 0xff & color;
 			if(contr->dark_mode == 1 )
 			{
 				float cur = contr->res_h / (2.0f * y - contr->res_h);
 				float yo = 1.0f - cur / VIEW_DIST;
 				if (yo < 0.0f)
 					yo = 0.0f;
 				else if (yo > 1.0f)
 					yo =  1.0f;
 				R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 				G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 				B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);
 			}
      		p_px(contr, x, contr->res_h - y - 1, R + G + B );
      	}
    }
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
	double ZBuffer[contr->res_w];
	// pthread_t thread_id;
	// pthread_create(&thread_id, NULL, draw_floor, contr); 
    // pthread_join(thread_id, NULL); 
	//drawback(contr);
	draw_floor(contr);
	x = -1;

		  	   // FLOOR CASTING

	// pthread_join(thread_id, NULL);
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
		int testx, testy;

		if (rayDirX < 0)
		{
			testx = 0;
			stepX = -1;
			sideDistX = (pos.x - mapX) * deltaDistX;
	  	}
	  	else
	 	{
			testx = 1;
			stepX = 1;
			sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			testy = 1;
			stepY = -1;
			sideDistY = (pos.y - mapY) * deltaDistY;
		}
		else
		{
			testy = 0;
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
  	      	//printf("THERE %d %d \n", mapX, mapY);
  	      	//printf("HERE IS %c THE CHAR\n", contr->map[mapX][mapY]);
        	if (contr->map[mapX][mapY] > '0')
        		hit = 1;
        	
      	}
      	if(side == 0)
      		perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
      	else
      		perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY; 
			
      	int lineHeight = (int)(contr->res_h / perpWallDist);
      	t_vp tmp;
      	tmp.x = deltaDistX;
      	tmp.y = deltaDistY;

      	int drawStart = -lineHeight / 2 + contr->res_h / 2;
      	int drawEnd = lineHeight / 2 + contr->res_h / 2;

      	if(drawStart < 0)
      		drawStart = 0;
      	if(drawEnd >= contr->res_h)
      		drawEnd = contr->res_h - 1;


      	double wallX; //where exactly the wall was hit
      	if (side == 0)
      		wallX = pos.y + perpWallDist * rayDirY;
      	else
        	wallX = pos.x + perpWallDist * rayDirX;
      	wallX -= floor((wallX));
		//tester avec step X et step Y + side pour le cote du mur
      	int texX = (int)(wallX * (double)contr->textures[side].w);
      	if(side == 0 && rayDirX > 0)
      		texX = contr->textures[side].w - texX - 1;
      	if(side == 1 && rayDirY < 0)
      		texX = contr->textures[side].w - texX - 1;
		
		int texture = 0;
		if(side == 1 && stepY > 0)
			texture = 0;
		else if (side == 1 && stepY < 0)
			texture = 1;
		else if(side == 0 && stepX > 0)
			texture = 2;
		else if(side == 0 && stepX < 0)
			texture = 3;
      	// printf("%d\n",side + stepY + stepX );
  	 	double step = 1.0 * contr->textures[side].w / lineHeight;
      	double texPos = (drawStart - contr->res_h / 2 + lineHeight / 2) * step;
		


      	for(int y = drawStart; y<drawEnd; y++)
      	{
        	int texY = (int)texPos; //& (225 - 1);
        	texPos += step;
	  		int colorT	= g_px(contr->textures[texture], texX,texY);// + perpWallDist * 0xA1A1A1;
	       	

	  		

	      // 	if(side == 1)
			//	colorT = (colorT >> 1) & 8355711;
 			int R, G, B;
 			R = 0xff0000 & colorT;
 			G = 0xff00 & colorT;
 			B = 0xff & colorT;
  			if(contr->dark_mode == 1)
  			{
 				float yo = (1.0f - perpWallDist / VIEW_DIST);
 				if (yo < 0.0f)
 					yo = 0.0f;
 				else if (yo > 1.0f)
 					yo =  1.0f;
 				R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 				G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 				B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);

  			}
			p_px(contr, x, y, R+G+B);   	
      	}
      	ZBuffer[x] = perpWallDist;
      	//int color = 0x484848;

     	
      	// printf("%d\n",g_px(contr->texture, 224,224));
      //	if (side == 1)
      	//	color = 0x282828;
	}
	
	spritecast(contr,ZBuffer);

}





