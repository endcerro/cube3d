#include "../header/header.h"


void sortSprites(int* order, double* dist, int amount)
{
 
}
void spritecast(t_contr *contr, double *ZBuffer)
{
	//SPRITE CASTING
	
    //sort sprites from far to close
   	int 	numSprites = 1;
    int 	spriteOrder[numSprites];
	double 	spriteDistance[numSprites];
    double 	posX = contr->pos.x;
    double 	posY = contr->pos.y;
    double 	dirY = contr->dir.y;
    double 	dirX = contr->dir.x;
    double 	planeY = contr->plane.y;
    double 	planeX = contr->plane.x;
    int w = contr->res_w;
    int h = contr->res_w;
    t_sprite sprite[numSprites];
    sprite[0].x = 8;
    sprite[0].y = 8;
    sprite[0].texture = contr->textures[3];

    spriteOrder[0] = 1;
    spriteDistance[0] = 1;

    for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
    }
    // sortSprites(spriteOrder, spriteDistance, numSprites);

    // //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
    	double spriteX = sprite[spriteOrder[i]].x - posX;
    	double spriteY = sprite[spriteOrder[i]].y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

    	double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

    	double transformX = invDet * (dirY * spriteX - dirX * spriteY);
    	double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

    	int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

       //calculate height of the sprite on screen
    	int spriteHeight = ft_abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      // //calculate lowest and highest pixel to fill in current stripe
    	int drawStartY = -spriteHeight / 2 + h / 2;
      	if(drawStartY < 0) drawStartY = 0;
      		int drawEndY = spriteHeight / 2 + h / 2;
      	if(drawEndY >= h) drawEndY = h - 1;

      // //calculate width of the sprite
      	int spriteWidth = ft_abs( (int) (h / (transformY)));
      	int drawStartX = -spriteWidth / 2 + spriteScreenX;
      	if(drawStartX < 0)
      		drawStartX = 0;
  		int drawEndX = spriteWidth / 2 + spriteScreenX;
      	if(drawEndX >= w)
      		drawEndX = w - 1;

      // //loop through every vertical stripe of the sprite on screen
      	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      	{
        	//printf("HERE\n");
        	int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprite[0].texture.w / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        	if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        			{
          			//	printf("HERE 2 \n");
          				int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          				int texY = ((d * sprite[0].texture.h) / spriteHeight) / 256;
          				int color = g_px(contr->textures[3], texX,texY);
          				if((color & 0x00FFFFFF) != 0)
          				{
          					p_px(contr, stripe, y ,color);//[y][stripe] = color;
          				}
          //paint pixel if it isn't black, black is the invisible color
        		}
    	}
      }
   
}