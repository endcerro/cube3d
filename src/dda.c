/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:34:02 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/17 18:34:55 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"


#define VIEW_DIST 8

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
		while(++j < contr->res_w && (contr->res_h / (2.0f * j - contr->res_h)) > VIEW_DIST)
		{
			int color;
        	color = ceil;
			int R, G, B;
 			R = 0xff0000 & color;
 			G = 0xff00 & color;
 			B = 0xff & color;
 			// if(contr->dark_mode == 1 )
 			// {
 			// 	float cur = contr->res_h / (2.0f * j - contr->res_h);
 			// 	float yo = 1.0f - cur / VIEW_DIST;
 			// 	if (yo < 0.0f)
 			// 		yo = 0.0f;
 			// 	else if (yo > 1.0f)
 			// 		yo =  1.0f;
 			// 	R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
 			// 	G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
 			// 	B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);
 			// }
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
				// float cur = contr->res_h / (2.0f * y - contr->res_h);
 			// 	float yo = 1.0f - cur / VIEW_DIST;
 				float cur = contr->res_h / (2.0f * i - contr->res_h);
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

// void draw_col2(t_contr *contr, t_vpi *vals, int tx_id, double step, int x, double perpWallDist)
void draw_col2(t_contr *contr, t_vpi draw_v, t_vp tex_m, int tx_id, double step, int x, double perpWallDist)
{
	for(int y = draw_v.x; y < draw_v.y; y++)
  	{
		tex_m.y += step;
  		int colorT	= g_px(contr->textures[tx_id], tex_m.x, tex_m.y);
		
	  	t_color color;
		
		color.r = 0xff0000 & colorT;
		color.g = 0xff00 & colorT;
		color.b = 0xff & colorT;
		if(contr->dark_mode == 1)
		{
			float yo = (1.0f - perpWallDist / VIEW_DIST);
			if (yo < 0.0f)
				yo = 0.0f;
			else if (yo > 1.0f)
				yo =  1.0f;
			color.r = ((int)((double)0x0 + (color.r - 0x0) * yo) & 0xFF0000);
			color.g = ((int)((double)0x0 + (color.g - 0x0) * yo) & 0xFF00);
			color.b = ((int)((double)0x0 + (color.b - 0x0) * yo) & 0xFF);
		}
		p_px(contr, x, y, color.r + color.g + color.b);   	
  	}
}

int hitWall(t_contr *contr, t_vp side_dist, t_vp delta_dist, t_vpi *map, t_vpi step)
{
	int hit;
	int side;
	hit = 0;
	
		while (hit == 0)
      	{
        	//JUMP TO THE NEAREST WALL;
        	side = (side_dist.x < side_dist.y) ? 0 : 1;
        	if (side_dist.x < side_dist.y && (map->x += step.x))
          		side_dist.x += delta_dist.x;
        	else if (map->y += step.y)
          		side_dist.y += delta_dist.y;

        	//CHECK IF WALL HITS
  	      	if (contr->map[map->x][map->y] == '1')
        		hit = 1;
      	}
      	return (side);
}

int get_tx_id(int side, t_vpi step)
{
	if(side == 1 && step.y > 0)
		return (0);
	else if (side == 1 && step.y < 0)
		return (1);
	else if(side == 0 && step.x > 0)
		return (2);
	else
		return (3);
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

	t_col_rend r;

	double ZBuffer[contr->res_w];
	#ifdef BONUS
		draw_floor(contr);
	#else
		drawback(contr);
	#endif
	x = -1;
		  	   // FLOOR CASTING

	// pthread_join(thread_id, NULL);
	while(++x < contr->res_w)
	{
		//CREATING RAY USING THE CAMERA PLANE, LEFT = -1 -> 1
		double cameraX = 2 * x / (double)contr->res_w - 1;
		double rayDirX = dir.x + plane.x * cameraX;
		double rayDirY = dir.y + plane.y * cameraX;


		//GETTING OUR POSITION IN THE MAP 
		t_vpi map;
		map.x = (int)pos.x;
		map.y = (int)pos.y;

		//DDA PART
		//CREATING DISTANCE VARS
		t_vp side_dist;

	   	//SIMPLIFICATION OF PYTHAGORAS TO GET WALL DISTANCE
		t_vp delta_dist;

		delta_dist.x = fabs(1 / rayDirX);
		delta_dist.y = fabs(1 / rayDirY);
		double perpWallDist;


		//VARS CONTAINING THE DIRECTION TO GO TO CHECK FOR WALL -1 || 1
		t_vpi step;
		// int stepX;
		// int stepY;

		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		
		//GET DIRECTION
		step.y = (rayDirY < 0) ? -1 : 1;
		step.x = (rayDirX < 0) ? -1 : 1;

		//AND DISTANCE TO CHECK FOR WALL
		if (rayDirX < 0)
			side_dist.x = (pos.x - map.x ) * delta_dist.x;
	  	else
			side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
		if (rayDirY < 0)
			side_dist.y = (pos.y - map.y) * delta_dist.y;
		else
			side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
		


		side = hitWall(contr, side_dist, delta_dist, &map, step);

      	if(side == 0)
      		perpWallDist = (map.x - pos.x + (1 - step.x) / 2) / rayDirX;
      	else
      		perpWallDist = (map.y - pos.y + (1 - step.y) / 2) / rayDirY; 
		
		//HEIGHT OF THE WALL IN PIXELS
      	int lineHeight = (int)(contr->res_h / perpWallDist);
      	
      	//START->ENDING POINT OF THE LINE 
      	

      	t_vpi draw_v;

      	//CHECK AND CORRECT IF OFF SCREEN
      	draw_v.x = (-lineHeight / 2 + contr->res_h / 2 < 0) ? 0 :
      		-lineHeight / 2 + contr->res_h / 2;
      	draw_v.y = (lineHeight / 2 + contr->res_h / 2 > contr->res_h) ? 
      		contr->res_h : (lineHeight / 2 + contr->res_h / 2);

      	//PART OF THE WALL THAT HAS BEEN HIT DEPENDINGG ON ITS SIDE;
      	double wallX;
      	wallX = (side == 0) ? pos.y + perpWallDist * rayDirY :
      		pos.x + perpWallDist * rayDirX;
      	//REMOVING INT PART
      	wallX -= floor(wallX);
		
		//X AXIS OF TEXTURE (MAPPING)
		t_vp tex_m;
      	tex_m.x = (int)(wallX * (double)contr->textures[side].w);
  		tex_m.x = contr->textures[side].w - tex_m.x - 1;

		//GETTING THE TEXTURE INDEX
		int tx_id = get_tx_id(side, step);
		
  	 	double tx_step = 1.0 * contr->textures[tx_id].w / lineHeight;
      	double texPos = (draw_v.x - contr->res_h / 2 + lineHeight / 2) * tx_step;
		tex_m.y = (draw_v.x - contr->res_h / 2 + lineHeight / 2) * tx_step - tx_step;

		// t_col_rend render;
		// if(contr->dark_mode == 0  || 0.05f -  perpWallDist / VIEW_DIST > 0.0f )
		// {
		draw_col2(contr, draw_v, tex_m, tx_id, tx_step, x, perpWallDist);

	   
      	ZBuffer[x] = perpWallDist;
	}
	
	spritecast(contr,ZBuffer);

}





