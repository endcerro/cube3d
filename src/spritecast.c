/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:23:38 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/20 16:40:31 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/header.h"

#define VIEW_DIST 8
#define RATIO 7

void sort_sprites(double *spriteDistance, int *spriteOrder, int cpt)
{
	int i = 0;
	while(i < cpt - 1)
	{
		if(spriteDistance[spriteOrder[i]] < spriteDistance[spriteOrder[i + 1]])
		{
			int tmp = spriteOrder[i];
			spriteOrder[i] = spriteOrder[i + 1];
			spriteOrder[i + 1] = tmp;
			i = 0;
		}
		i++;
	}

}

void prep_sprites(t_contr *contr, t_sprite_rend *r)
{
	int i;
	
	i = -1;
  	while (++i < contr->sprites_nb)
  	{
		r->sprite_order[i] = i;
		r->sprite_distance[i] = ((contr->pos.x - contr->sprites[i].x) * 
			(contr->pos.x - contr->sprites[i].x) + (contr->pos.y - contr->sprites[i].y) * 
				(contr->pos.y - contr->sprites[i].y));
  	}
}

void get_draw_s_e(t_contr *contr, t_sprite_rend *r, int i)
{
	double invDet;

	r->sprite.x = r->sprites[r->sprite_order[i]].x - contr->pos.x;
	r->sprite.y = r->sprites[r->sprite_order[i]].y - contr->pos.y;
	invDet = 1.0 / (contr->plane.x * contr->dir.y - contr->dir.x * 
		contr->plane.y);
	r->transform.x = invDet * (contr->dir.y * r->sprite.x - contr->dir.x *
		r->sprite.y);
	r->transform.y = invDet * (-contr->plane.y * r->sprite.x + contr->plane.x
		* r->sprite.y);
	r->spriteScreenX = (int)((contr->res_w / 2) * (1 + r->transform.x / 
		r->transform.y));
	r->sprite_d.x = abs((int)(contr->res_h / (r->transform.y)));
   	r->draw_start.y = (-r->sprite_d.x / 2 + contr->res_h / 2 < 0) ? 0 
   		: -r->sprite_d.x / 2 + contr->res_h / 2;
	r->draw_end.y = (r->sprite_d.x / 2 + contr->res_h / 2 >= contr->res_h) ? 
		contr->res_h - 1 : r->sprite_d.x / 2 + contr->res_h / 2;
  	r->sprite_d.y = abs((int)(contr->res_h / (r->transform.y)));
  	if((r->draw_start.x = -r->sprite_d.y / 2 + r->spriteScreenX) && 
  			r->draw_start.x < 0)
		r->draw_start.x = 0;
	if((r->draw_end.x = r->sprite_d.y / 2 + r->spriteScreenX) && 
			r->draw_end.x >= contr->res_w)
		r->draw_end.x = contr->res_w - 1;
}

void draw_stripe(t_contr *contr,t_sprite_rend *r, double *buffer, int i, int stripe)
{
	t_vpi tex_p;
	int d;
	int colorT;
	tex_p.x = (int)(256 * (stripe - (-r->sprite_d.y / 2 + r->spriteScreenX)) * r->sprites[i].texture.w / r->sprite_d.y) / 256;
	if (r->transform.y > 0 && stripe > 0 && stripe < contr->res_w && r->transform.y < buffer[stripe])
		for(int y = r->draw_start.y; y < r->draw_end.y; y++)
		{
			d = (y) * 256 - contr->res_h * 128 + r->sprite_d.x * 128;
			tex_p.y = ((d * r->sprites[r->sprite_order[i]].texture.h) / r->sprite_d.x) / 256;
			colorT = g_px(r->sprites[r->sprite_order[i]].texture, tex_p.x,tex_p.y);
			
			// int R, G, B;
			// R = 0xff0000 & colorT;
			// G = 0xff00 & colorT;
			// B = 0xff & colorT;
			if((colorT & 0x00FFFFFF) != 0)	// && spriteDistance[numSprites - 1] < 8.0)
			{
				int R, G, B;
				R = 0xff0000 & colorT;
				G = 0xff00 & colorT;
				B = 0xff & colorT;
				if(contr->dark_mode == 1)
				{
					// printf(" to div = %f\n",r->sprite_distance[r->sprite_order[i]] );
					float yo = (1.0f - r->sprite_distance[r->sprite_order[i]] / (VIEW_DIST));// * (6.0 * (fabs(contr->dir.x) + fabs(contr->dir.y)))) );
					if (yo < 0.0f)
						yo = 0.0f;
					else if (yo > 1.0f)
						yo =  1.0f;
					R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
					G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
					B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);

				}
					p_px(contr, stripe, y ,R + G + B);//[y][stripe] = color;
			}		
		}
}
void spritecast(t_contr *contr, double *ZBuffer)
{
	//SPRITE CASTING
	
	//sort sprites from far to close
	// int 	numSprites = 1;
	int			i;
  	int			numSprites = contr->sprites_nb;
  	int			spriteOrder[numSprites];
  	double		spriteDistance[numSprites];
//  	double 		cache;
//  	int 		cache2;
  	t_vp 		dir;
  	t_vp 		pos;
  	t_vp 		plane;
  	t_vp 		transform;
  	t_vpi		draw_start;
  	t_vpi		draw_end;
  	t_vp 		sprite;
  	int w = contr->res_w;
  	int h = contr->res_h;
//POSSIBLE ERROR ROOT
  	t_sprite *sprites = contr->sprites;
	
  	pos = contr->pos;
  	plane = contr->plane;
  	dir = contr->dir;
  	
  	i = -1;
  	while(++i < numSprites)
  	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((pos.x - sprites[i].x) * (pos.x - sprites[i].x) + (pos.y - sprites[i].y) * (pos.y - sprites[i].y));
  	}
	sort_sprites(spriteDistance, spriteOrder,numSprites);
 	i = -1;
 	while(++i < numSprites)
  	{
	  
	 	sprite.x = sprites[spriteOrder[i]].x - pos.x;
		sprite.y = sprites[spriteOrder[i]].y - pos.y;
	  	
	
		double invDet = 1.0 / (plane.x * dir.y - dir.x * plane.y); //required for correct matrix multiplication

		transform.x = invDet * (dir.y * sprite.x - dir.x * sprite.y);
		transform.y = invDet * (-plane.y * sprite.x + plane.x * sprite.y); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((w / 2) * (1 + transform.x / transform.y));

	   int spriteHeight = ft_abs((int)(h / (transform.y))); //using 'transformY' instead of the real distance prevents fisheye
	  // //calculate lowest and highest pixel to fill in current stripe
		draw_start.y = -spriteHeight / 2 + h / 2;
		//int drawStartY = -spriteHeight / 2 + h / 2;
		if(draw_start.y < 0)
		 	draw_start.y = 0;
		draw_end.y =  spriteHeight / 2 + h / 2;
		if(draw_end.y >= h)
			draw_end.y = h - 1;

	  // //calculate width of the sprite
		int spriteWidth = ft_abs( (int) (h / (transform.y)));
		
		//int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if((draw_start.x = -spriteWidth / 2 + spriteScreenX) && draw_start.x < 0)
			draw_start.x = 0;
		
		//int drawEndX = spriteWidth / 2 + spriteScreenX;
		if((draw_end.x = spriteWidth / 2 + spriteScreenX) && draw_end.x >= w)
			draw_end.x = w - 1;

	  // //loop through every vertical stripe of the sprite on screen
		for(int stripe = draw_start.x; stripe < draw_end.x; stripe++)
		{
			//printf("HERE\n");
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprites[i].texture.w / spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
			printf(" to div = %f\n",spriteDistance[spriteOrder[i]] );
			if(transform.y > 0 && stripe > 0 && stripe < w && transform.y < ZBuffer[stripe])
				for(int y = draw_start.y; y < draw_end.y; y++) //for every pixel of the current stripe
					{
				  		// printf(" to div = %f\n",spriteDistance[spriteOrder[i]] );

					//	printf("HERE 2 \n");
						int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
						int texY = ((d * sprites[spriteOrder[i]].texture.h) / spriteHeight) / 256;
						int colorT = g_px(sprites[spriteOrder[i]].texture, texX,texY);
						if((colorT & 0x00FFFFFF) != 0)	// && spriteDistance[numSprites - 1] < 8.0)
						{
							int R, G, B;
							R = 0xff0000 & colorT;
							G = 0xff00 & colorT;
							B = 0xff & colorT;
							if(contr->dark_mode == 1)
							{
								float yo = (1.0f - spriteDistance[spriteOrder[i]] / (VIEW_DIST * (6.0 * (fabs(contr->dir.x) + fabs(contr->dir.y)))) );
								if (yo < 0.0f)
									yo = 0.0f;
								else if (yo > 1.0f)
									yo =  1.0f;
								R = ((int)((double)0x0 + (R - 0x0) * yo) & 0xFF0000);
								G = ((int)((double)0x0 + (G - 0x0) * yo) & 0xFF00);
								B = ((int)((double)0x0 + (B - 0x0) * yo) & 0xFF);

							}
							//if(spriteDistance[numSprites] > 0.0)
								//printf("%f\n",spriteDistance[numSprites - 1]);
							p_px(contr, stripe, y ,R + G + B);//[y][stripe] = color;
						}
		  //paint pixel if it isn't black, black is the invisible color
				}
		}
	  }
   
}
