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
        	int tx = (int)(contr->textures[5].w * (floorX - cellX)) & (contr->textures[5].w - 1);
        	int ty = (int)(contr->textures[5].h * (floorY - cellY)) & (contr->textures[5].h - 1);

        	floorX += floorStepX;
        	floorY += floorStepY;

        	int color;
        	color = g_px(contr->textures[5], tx,ty);
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
        	color = g_px(contr->textures[5], tx,ty);
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
