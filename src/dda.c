/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 23:31:42 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int get_face(t_contr *contr, t_vp ray, double dist)
{

	t_vp contact;

	printf("%f\n",ray.y );
	
	if(!isinf(ray.x))
		contact.x = ray.x + contr->pos.x; //* dist;
	if(!isinf(ray.y))
		contact.y = ray.y + contr->pos.y;// * dist;

	
	printf("contact %d %d\n",(int)contact.x, (int)contact.y );


	return(0);

}


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
	ceil = 0x969696;
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
        	int tx = (int)(contr->textures[2].h * (floorX - cellX)) & (contr->textures[2].h - 1);
        	int ty = (int)(contr->textures[2].h * (floorY - cellY)) & (contr->textures[2].h - 1);

        	floorX += floorStepX;
        	floorY += floorStepY;

        	int color;
        	color = g_px(contr->textures[2], tx,ty);
        	color = (color >> 1) & 8355711; // make a bit darker

        	p_px(contr, x, y, color);
        	
        	color = g_px(contr->textures[3], tx,ty);
      		
      		p_px(contr, x, contr->res_h - y - 1, color );
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
	// pthread_t thread_id;
	// pthread_create(&thread_id, NULL, draw_floor, contr); 
    // pthread_join(thread_id, NULL); 
	// drawback(contr);
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
        	if (contr->map[mapX][mapY] > 0)
        		hit = 1;
      	}
      	if(side == 0)
      		perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
      	else
      		perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY; 
			
	  // 	if(x == contr->res_w /2)
	  // 	{
	  // 		//int test = rayDirX 
	  // 		printf("ray_dir = %f %f\n",rayDirX, rayDirY );
			// printf("wallD = %f \n", perpWallDist);
	  // 	}
      	int lineHeight = (int)(contr->res_h / perpWallDist);
      	t_vp tmp;
      	tmp.x = deltaDistX;
      	tmp.y = deltaDistY;


	  	if(x == contr->res_w /2)
	  	{
	  		//int test = rayDirX 
//	  		printf("ray_dir = %f %f\n",rayDirX, rayDirY );
//			printf("wallD = %f \n", perpWallDist);
	      	get_face(contr, tmp, lineHeight);
	  	}

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

      	int texX = (int)(wallX * (double)contr->textures[side].w);
      	if(side == 0 && rayDirX > 0)
      		texX = contr->textures[side].w - texX - 1;
      	if(side == 1 && rayDirY < 0)
      		texX = contr->textures[side].w - texX - 1;

      	// printf("%d\n",side + stepY + stepX );
  	 	double step = 1.0 * contr->textures[side].w / lineHeight;
      	double texPos = (drawStart - contr->res_h / 2 + lineHeight / 2) * step;
		


      	for(int y = drawStart; y<drawEnd; y++)
      	{
        	int texY = (int)texPos; //& (225 - 1);
        	texPos += step;
	  		int colorT	= g_px(contr->textures[side], texX,texY);// + perpWallDist * 0xA1A1A1;
	       	

	  		

	       	if(side == 1) colorT = (colorT >> 1) & 8355711;
 			int R, G, B;
 			R = 0xff0000 & colorT;
 			G = 0xff00 & colorT;
 			B = 0xff & colorT;
  			if(contr->dark_mode == 1)
  			{
	  			for (int i =0; i< perpWallDist; i++)
	  			{
		       		if(R > 0x0A0000)
		       			R -= 0x0A0000;
		       		else
		       			R = 0; 
	  				if(G > 0x000A00)
	  					G -= 0x000A00;
	  				else
		       			G = 0;
	  				if(B > 0x00000A)
	  					B -= 0x00000A;
	  				else
	  					B = 0;
	  			}
  			}
			p_px(contr, x, y, R+G+B);      	
      	}

      	int color = 0x484848;

     
      	// printf("%d\n",g_px(contr->texture, 224,224));
      	if (side == 1)
      		color = 0x282828;


      	// printf("out\n");
      	// draw_col(x, drawStart, drawEnd, color, contr);
	}

}





