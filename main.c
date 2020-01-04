#include "header/header.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

int draw_plane(int *coords, t_contr *contr)
{
	int i = 0;
	int j = 0;

	while(i + coords[0] < coords[2])
	{
		while (j + coords[1] < coords[3])
		{
			mlx_pixel_put(contr->mlx_ptr, contr->win_ptr,  i + coords[0],  j + coords[1], 0x00FFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	return 0;
}




char matchkey(int key)
{
	if(key == 13)
		return ('w');
	else if(key == 0)
		return ('a');
	else if(key == 1)
		return ('s');
	else if(key == 2)
		return ('d');
	else if(key == 49)
		return (' ');
	else if(key == 53)
		exit(0);

	return ('?');
}


int process_key(int key, void *params)
{
	(void)params;
	printf("key = %c\n", matchkey(key));
	return (0);
}


int process_mouse(int btn, int x, int y, void *params)
{
	//(void)params;

	t_contr *contr;
	contr = (t_contr *)params;
	
	// printf("x = %d y = %d ", x, y);
	// if (btn == 1)
	// 	printf("right click\n");
	// else if (btn == 2)
	// 	printf("left click\n");
	// else if (btn == 3)
	// 	printf("wheel click\n");
	// else if (btn == 4)
	// 	printf("wheel up\n");
	// else if (btn == 5)
	// 	printf("wheel down\n");
	// else
	// 	printf("nani\n");

	int test[4] = {x,y,x + 120, y + 120};
	draw_plane(test, contr);

	mlx_pixel_put(contr->mlx_ptr, contr->win_ptr,  x,  y, 0x00FF0000);

	return (0);
}

int voidprocess(void *params)
{
	//write(1,"REFRESH",7);
	//(void)params;
	//write(1,"REFRESH",7);
	t_contr *contr;
	contr = (t_contr *)params;
	// //int coords[4] = {0,0,120,120};
	// //int test = 2;
	// // //mlx_pixel_put(contr->mlx_ptr, contr->win_ptr,  5,  7, 0x00FFFFFF);
	// // draw_plane(coords, contr);
	// //printf("here\n");
	// // int blanc = 0x00FFFFFF;
	// // int rouge = 0x00FF0000;
	// // int bleu = 0x000000FF;
	// // int vert = 0x0000FF00;
	mlx_string_put(contr->mlx_ptr, contr->win_ptr, 0, 0, 0x00FF0000, "Hello world");
	return (0);
}

int main()
{

	int blanc = 0x00FFFFFF;
	int rouge = 0x00FF0000;
	int bleu = 0x000000FF;
	int vert = 0x0000FF00;
	//int blanc = 0x00FFFFFF;
	t_contr contr;
	

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	contr.map_h = 4;
	contr.map_w = 4;
	//contr.map = map;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 640, 480, "test");
	
	contr.mlx_ptr = mlx_ptr;
	contr.win_ptr = win_ptr;

//	void (*fun_ptr)(void*) = &voidprocess; 

	mlx_key_hook(win_ptr, process_key, (void *)&contr);
	mlx_mouse_hook (win_ptr, process_mouse, (void *)&contr);
	mlx_loop_hook(mlx_ptr, voidprocess, (void *)&contr);
	//mlx_hook(win_ptr,0,0, voidprocess, (void *)&contr);
	
	//printf("int = %d \n",color );


	//mlx_string_put(mlx_ptr, win_ptr, 0, 0, rouge, "Hello world");
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, blanc);
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, 250);
	// /mlx_string_put()
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
	free(win_ptr);
	return 0;
}