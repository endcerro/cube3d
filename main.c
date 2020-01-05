#include "header/header.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

int draw_plane(int *coords, t_contr *contr, int color)
{
	int i = 0;
	int j = 0;

	int c0 = coords[0];
	int c1 = coords[1];
	int c2 = coords[2];
	int c3 = coords[3];

	while(i + c0 < c2)
	{
		while (j + c1 < c3)
		{
			mlx_pixel_put(contr->mlx_ptr, contr->win_ptr,  i + c0,  j + c1, color);
			j++;
		}
		j = 0;
		i++;
	}
	return 0;
}

int draw_col(int *coords, t_contr *contr)
{

	int col = coords[0];
	int start = coords[1];
	int end = coords[2];


	int i = 0;
	int j = 0;

	while (i < contr->res_h)
	{
		if(start <= i && i <= end)
			mlx_pixel_put(contr->mlx_ptr, contr->win_ptr, col, i, 0x00FFFFFF);
		else
			mlx_pixel_put(contr->mlx_ptr, contr->win_ptr, col, i, 0x00000000);
		i++;
	}
	
	return 0;
}

void draw(t_contr *params)
{
	
	int x;
	x = 0;
	//return(0);
}




























































int draw_top_down_map(t_contr *contr)
{
	int pas_x = contr->res_w / contr->map_w;
	int pas_y = contr->res_h / contr->map_w;
	
	double pasx= contr->p_x * pas_x;
	double pasy= contr->p_x * pas_x;
	// /printf("\n");
	int ree[4] ={pasx, contr->p_y * pas_y, pasx + pas_x, contr->p_y * pas_y + pas_y};
	draw_plane(ree,	contr,0x0000FF00);
	//printf("pas = %d\n",pas );
	int **map = contr->map;

	int i= 0;
	int j= 0;
	int drawn = 0;
	while(i < contr->map_w)
	{
		while(j < contr->map_w)
		{
			int test[4] = {j * pas_x, i * pas_y, j * pas_x + pas_x, i * pas_y + pas_y};
			if(map[i][j] == 1)
			{
				//int test[4] = {j * pas_x, i * pas_y, j * pas_x + pas_x, i * pas_y + pas_y};
				//printf("%d %d %d %d \n",i*pas,j*pas,j*pas + pas,pas );
				draw_plane(test,contr, 0x00FFFFFF);
			}
			else
				draw_plane(test,contr, 0x00000000);
			j++;
		}	
		j = 0;
		i++;
	}
	int test2[4] = {contr->p_x, contr->p_y, contr->p_x + 20, contr->p_y + 20};
	draw_plane(test2,contr, 0x0FF00000);
	//printf("fini %d\n", drawn);
	return (0);
}

char matchkey(int key)
{
	printf("key = %d\n",key );
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

	int test[4] ={0,0,640,480};
	t_contr *contr;
	contr = (t_contr *)params;
	//draw_plane(test, contr, 0x00000000);
	char c = matchkey(key);	
	double moveSpeed = 100.0f;

	printf("x = %f y = %f\n",contr->p_x, contr->p_y );
	if (c == 'w')
	{
	//	printf("ici\n");
		contr->p_x += contr->dir_x * moveSpeed;
		contr->p_y += contr->dir_y * moveSpeed;
	}
	else if (c == 's')
	{
	//s	printf("la\n");
		contr->p_x -= contr->dir_x * moveSpeed;
		contr->p_y -= contr->dir_y * moveSpeed;
	}
	else if (c == 'a')
	{
	//s	printf("la\n");
		contr->planeX -= contr->dir_x * moveSpeed;
		contr->planeY -= contr->dir_y * moveSpeed;
	}
	else if (c == 'd')
	{
	//s	printf("la\n");
		contr->planeX -= contr->dir_x * moveSpeed;
		contr->planeY -= contr->dir_y * moveSpeed;
	}
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

	//int test[4] = {x,y,x + 120, y + 120};
	//draw_plane(test, contr, 0x00FFFFFF);

	//mlx_pixel_put(contr->mlx_ptr, contr->win_ptr,  x,  y, 0x00FF0000);

	return (0);
}


int voidprocess(void *params)
{
	//draw(params);
	//int test[4] = {0,0,1, 400};
	//draw_plane(test, (t_contr *)params, 0x00FFFFFF);
	draw_top_down_map((t_contr *)params);
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
	

	// contr.map_h = 4;
	// contr.map_w = 4;
	//contr.map = map;
	void *mlx_ptr;
	void *win_ptr;

	contr.res_w = 640;
	contr.res_h = 480;

	contr.dir_x = -1;
	contr.dir_y = 0;

	contr.planeX = 0;
	contr.planeY = 0.66;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, contr.res_w, contr.res_h, "test");
	
	contr.mlx_ptr = mlx_ptr;
	contr.win_ptr = win_ptr;

//	void (*fun_ptr)(void*) = &voidprocess; 

	mlx_key_hook(win_ptr, process_key, (void *)&contr);
	mlx_mouse_hook (win_ptr, process_mouse, (void *)&contr);
	mlx_loop_hook(mlx_ptr, voidprocess, (void *)&contr);
	//mlx_hook(win_ptr,0,0, voidprocess, (void *)&contr);
	load_map("map/1.mp", &contr);
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