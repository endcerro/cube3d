#include "header/header.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

void            my_mlx_pixel_put(t_contr *contr, int x, int y, int color)
{
    char    *dst;
    t_img img;
    img = contr->img;
    dst = img.addr + (y * img.length + x * (img.bpp / 8));
    *(unsigned int*)dst = (unsigned int)color;
}

void print_image(t_contr *contr, int x, int y)
{

	//printf("RENDERED");
	mlx_clear_window(contr->mlx_ptr, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx_ptr, contr->win_ptr, (contr->img).img, x, y);
   	mlx_destroy_image(contr->mlx_ptr, contr->img.img);

   	contr->img.img = mlx_new_image(contr->mlx_ptr, contr->res_w, contr->res_h);
	contr->img.addr =  mlx_get_data_addr(contr->img.img, &(contr->img.bpp), &(contr->img.length), &(contr->img.endian));

}


void draw_line_new(double x1, double y1, double x2, double y2, t_contr *contr, int color){
	
	double x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	dx1 = ft_abs_double(dx);
	dy1 = ft_abs_double(dy);
	
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; 
			y = y1; 
			xe = x2;
		} 
		else 
		{ // Line is drawn right to left (swap ends)
			x = x2; y = y2; xe = x1;
		}
		my_mlx_pixel_put(contr, x, y, color);
				//pixel(x, y); // Draw first pixel
				
				// Rasterize the line
		for(i = 0; x < xe; i++) 
		{
			x = x + 1;		
						// Deal with octants...
			if (px < 0) 
			{
				px = px + 2 * dy1;
			} 
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) 
				{
					y = y + 1;
				} 
				else 
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
					
						// Draw pixel from line span at
						// currently rasterized position
			my_mlx_pixel_put(contr, x, y, color);
		}
				
	} 
	else 
	{ // The line is Y-axis dominant
			
				// Line is drawn bottom to top
		if (dy >= 0) 
		{
			x = x1; 
			y = y1; 
			ye = y2;
		} 
		else 
		{ // Line is drawn top to bottom
			x = x2; y = y2; ye = y1;
		}
		my_mlx_pixel_put(contr, x, y, color);	
		//pixel(x, y); // Draw first pixel
				
				// Rasterize the line
		for (i = 0; y < ye; i++) 
		{
			y = y + 1;
					
			// Deal with octants...
			if (py <= 0) 
			{
				py = py + 2 * dx1;
			} 
			else 
			{
				if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) 
				{
					x = x + 1;
				} 
				else 
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
					
						// Draw pixel from line span at
						// currently rasterized position
			my_mlx_pixel_put(contr, x, y, color);
				//	pixel(x, y);
		}
	}
}


int draw_square(double x_0, double y_0, double x_e, double y_e, t_contr *contr, int color)
{
	draw_line_new(x_0,y_0, x_e, y_0, contr, color);
	draw_line_new(x_0,y_0, x_0, y_e, contr, color);
	draw_line_new(x_e,y_0, x_e, y_e, contr, color);
	draw_line_new(x_0,y_e, x_e, y_e, contr, color);
	return 0;
}

// void cast_rays(t_contr *contr)
// {
// 	float fPlayerX = contr->p_x;
// 	float fPlayerY = contr->p_y;
// 	float fPlayerA = contr->angle;
	
// 	int nScreenWidth = contr->res_w;
// 	int nScreenHeight = contr->res_h;
	
// 	int nMapHeight = 7;
// 	int nMapWidth   = 7;


// 	float fFOV = M_PI / 4;
// 	for(int x =0; x < nScreenWidth; x++)
// 	{
// 		float fRayAngle = (fPlayerA -fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

// 		float fDistanceToWall = 0;
// 		int hit = 0;

// 		float fEyeX = sin(fRayAngle);
// 		float fEyeY  = cos(fRayAngle);

// 		while(!hit && fDistanceToWall < 7)
// 		{
// 			fDistanceToWall += 0.1f;

// 			int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
// 			int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

// 			if(nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
// 			{
// 				hit = 1;
// 				fDistanceToWall = 7;
// 			}
// 			else
// 			{
// 				//printf("nTest Y = %d , X = %d \n", nTestY, nTestX);
// 				if(contr->map[nTestY][nTestX] == 1)
// 				{
// 					printf("hit");
// 					hit = 1;
// 				}
// 			}
			
// 			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / (float) 


// 		//printf("ray_angle = %f\n", fRayAngle);
// 		}
// 	}

// 	//float ray_angle = contr->angle;


// 	// float fov = 60;
// 	// float ray_angle;
// 	// int i = 0;
// 	// int hit;
// 	// hit = 0;
// 	// int fDepth = 8.0f;

// 	// while(i < contr->res_w)
// 	// {
// 	// 	ray_angle = (contr->angle - fov / 2.0) + (i / contr->res_w) * fov; 
		
// 	// 	float fEyeX = sin(ray_angle);
// 	// 	float fEyeY = cos(ray_angle );
// 	// 	float fDistanceToWall = 0;

// 	// 	while(!hit && fDistanceToWall < fDepth)
// 	// 	{
// 	// 		fDistanceToWall += 0.1f;

// 	// 		int nTestX = (int)(contr->p_x + fEyeX * fDistanceToWall);
// 	// 		int nTestY = (int)(contr->p_y + fEyeY * fDistanceToWall);
			
// 	// 		if(nTestX < 0 || nTestX >= contr->map_w || nTestY < 0 || nTestY >= contr->map_w)
// 	// 		{
// 	// 			hit = 1;
// 	// 			fDistanceToWall = fDepth;
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			if(contr->map[nTestY][nTestX] == 1)
// 	// 			{
// 	// 				hit = 1;
// 	// 			}
// 	// 		}
// 	// 	}
// 	// 	int nCeiling = (float)(contr->res_h / 2.0) - contr->res_h / (float)fDistanceToWall;
// 	// 	int nFloor = contr->res_h - nCeiling;
// 	// 	for(int y =0; y < contr->res_h; y++)
// 	// 	{
// 	// 		if(y < nCeiling)
// 	// 		{
// 	// 			my_mlx_pixel_put(contr,i,y,0x00000000);
// 	// 		}
// 	// 		else if(y > nCeiling && y <= nFloor)
// 	// 		{
// 	// 			my_mlx_pixel_put(contr,i,y,0x00FF0000);
// 	// 		}
// 	// 	}
// 	// 	i++;
// 	// }
// 	// //printf("RENDERED");
// 	// print_image(contr, 0,0);

// 	// while(i < 60)
// 	// {


// 	// }

// }

int draw_top_down_map(t_contr *contr)
{

	int pas_x = contr->pas_x;
	int pas_y = contr->pas_y;
	int **map = contr->map;

	int i= -1;
	int j= 0;
	while(++i < contr->map_w)
	{
		while(j < contr->map_w)
		{
			if(map[i][j] == 1)
				draw_square(j * pas_x, i * pas_y, j * pas_x + pas_x,  i * pas_y + pas_y, contr, 0x00FF0000);
			j++;
		}
		j = 0;
	}
  	draw_square(contr->p_x - 10 , contr->p_y -10 , contr->p_x + 10, contr->p_y + 10, contr, 0x0000FFFF);
   	draw_line_new(contr->p_x   , contr->p_y  , (contr->p_x + (contr->dir_x * 100.0)), 
   		(contr->p_y +  (contr->dir_y * 100.0)), contr, 0x0000FF00);
   	print_image(contr,0,0);
	return (0);
}

int process_mouse(int btn, int x, int y, void *params)
{
	//(void)params;

	t_contr *contr;
	contr = (t_contr *)params;
	
	double step;

	step = 180;
	// printf("x = %d y = %d ", x, y);
	if (btn == 1)
		contr->angle += M_PI/step;
	else if (btn == 2)
		contr->angle -= M_PI/step;
	else if (btn == 4)
		contr->angle += M_PI/step;
	else if (btn == 5)
		contr->angle -= M_PI/step;
	contr->dir_x = cos(contr->angle);
	contr->dir_y = sin(contr->angle);
	return (0);
}


int voidprocess(void *params)
{
	//cast_rays((t_contr *)params);

	draw_top_down_map((t_contr *)params);
	return (0);
}

int sample()
{
	write(1,"EXPOSE",6);
	return(0);
}

int close_win(void *param)
{
    (void)param;
    exit(0);
}
int key_press(int key, void *param)
{
	t_contr *contr;
	double move_speed;

	double pas_pi= 180;

	move_speed = 3.5f;
	contr = (t_contr*)param;
	if (key == 13)
	{ //W
		draw_top_down_map(contr);
		contr->p_y += move_speed * contr->dir_y;
		contr->p_x += move_speed * contr->dir_x;
	}
	else if (key == 1) //s
	{
		contr->p_y -= move_speed * contr->dir_y;
		contr->p_x -= move_speed * contr->dir_x;
	} 
	else if (key == 0)
	{
		//contr->p_x
		contr->p_x -= move_speed;
	} //A
	else if (key == 2) //D
		contr->p_x += move_speed;
	else if(key == 125)
		contr->angle += M_PI/pas_pi;
	else if(key == 126)
		contr->angle -= M_PI/pas_pi;
	if(key == 53)
		exit(0);


	printf("pos x = %f y = %f\n",contr->p_x, contr->p_y );
	//ATTENTION CODE EXPLOSIF
	printf("REAL pos x = %d y = %d\n",(int)((contr->p_x * contr->map_w) / contr->res_w), (int)(contr->p_y * contr->map_w) / contr->res_h );
	//printf("key = %d \n",key );

	contr->value = contr->p_x * contr->pas_x;
	//printf("REAL pos x = %d\n",contr->value);

	contr->dir_x = (cos(contr->angle));
	contr->dir_y = (sin(contr->angle));
	return 0;
}
int key_release(int key,void *param)
{
	//printf("KEYUP = %d \n",key );
	return 0;
}

int main()
{
	t_contr contr;
	
	void *mlx_ptr;
	void *win_ptr;
	void *win_ptr2;

	void *img;

	contr.res_h = 1000;
	contr.res_w = 1200;

	contr.dir_x = 1;
	contr.dir_y = 0;
	contr.angle = 0;

	contr.planeX = 0;
	contr.planeY = 0.66;

	//contr.angle = 0;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, contr.res_w, contr.res_h, "test");
	// win_ptr2 = mlx_new_window(mlx_ptr, 5, 5, "test 2");
	
	t_img image;


	image.img = mlx_new_image(mlx_ptr, contr.res_w, contr.res_w);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;


	contr.mlx_ptr = mlx_ptr;
	contr.win_ptr = win_ptr;

//	void (*fun_ptr)(void*) = &voidprocess; 

	mlx_do_key_autorepeaton(mlx_ptr);
	//mlx_key_hook(win_ptr, process_key, (void *)&contr);
	mlx_mouse_hook (win_ptr, process_mouse, (void *)&contr);
	mlx_loop_hook(mlx_ptr, voidprocess, (void *)&contr);
	//mlx_expose_hook(win_ptr,sample, 0 );
	mlx_hook(win_ptr,17,0, close_win, (void *)&contr);
	mlx_hook(win_ptr,2,0, key_press, (void *)&contr);
	mlx_hook(win_ptr,3,0, key_release, (void *)&contr);
	load_map("map/1.mp", &contr);
	//printf("pos basique %f %f", contr.p_x, contr.p_y);
	//printf("int = %d \n",color );
	
	//mlx_do_sync(mlx_ptr);
	contr.pas_x = contr.res_w / contr.map_w;
	contr.pas_y = contr.res_h / contr.map_w;
	
	contr.value = contr.p_x * contr.pas_x;

	//contr.p_x = 250;
	//contr.p_y = 250;

	//mlx_string_put(mlx_ptr, win_ptr, 0, 0, RED, "Hello world");
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, blanc);
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, 250);
	// /mlx_string_put()
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
	free(win_ptr);
	return 0;
}