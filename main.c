#include "header/header.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

void            my_mlx_pixel_put(t_contr *contr, int x, int y, int color)
{
    char    *dst;

    t_img img;

    img = contr->img;

    dst = img.addr + ((y * img.length + x * (img.bpp / 8)));
    *(unsigned int*)dst = (unsigned int)color;
}

void print_image(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx_ptr, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx_ptr, contr->win_ptr, (contr->img).img, x, y);
   	mlx_destroy_image(contr->mlx_ptr, contr->img.img);

   	contr->img.img = mlx_new_image(contr->mlx_ptr, 640, 480);
	contr->img.addr =  mlx_get_data_addr(contr->img.img, &(contr->img.bpp), &(contr->img.length), &(contr->img.endian));

}

int testdraw_line(double x_s, double y_s, double x_e, double y_e, t_contr *contr, int color)
{
	t_point point;
	double max;
	double i;

	i = 0;
	point.x = x_e - x_s;
	point.y =y_e - y_s;
    max = ft_abs_double(point.y);
    if(ft_abs_double(point.x) > ft_abs_double(point.y))
    	max = ft_abs_double(point.x);
    point.x /= max;
    point.y /= max;
    while (i < max)
    {
    	my_mlx_pixel_put(contr, x_s, y_s, color);
    	//mlx_pixel_put(contr->mlx_ptr, contr->win_ptr, x_s, y_s, color);
        x_s += point.x; 
        y_s += point.y;
        i++;
    }
    return (0);
}


int draw_square(double x_0, double y_0, double x_e, double y_e, t_contr *contr, int color)
{
	testdraw_line(x_0,y_0, x_e, y_0, contr, color);
	testdraw_line(x_0,y_0, x_0, y_e, contr, color);
	testdraw_line(x_e,y_0, x_e, y_e, contr, color);
	testdraw_line(x_0,y_e, x_e, y_e, contr, color);
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
		i++;
	}
	
	return 0;
}

void draw(t_contr *params)
{
	
	int x;
	x = 0;
}

int draw_top_down_map(t_contr *contr)
{

	int pas_x = contr->pas_x;
	int pas_y = contr->pas_y;
	
	double pasx= contr->value;
	//mlx_
	int **map = contr->map;

	int i= 0;
	int j= 0;
	while(i < contr->map_w)
	{
		while(j < contr->map_w)
		{
			int test[4] = {j * pas_x, i * pas_y, j * pas_x + pas_x, i * pas_y + pas_y};
			if(map[i][j] == 1)
			{
				draw_square(j * pas_x, i * pas_y, j * pas_x + pas_x,  i * pas_y + pas_y, contr, 0x00FF0000);
			}
			j++;
		}	
		j = 0;
		i++;
	}
	int test2[4] = {contr->p_x * pas_x, contr->p_y * pas_y, contr->p_x * pas_x + 20, contr->p_y * pas_y + 20};
	//draw_square(contr->p_x * pas_x, contr->p_y * pas_y, contr->p_x * pas_x + 20, contr->p_y * pas_y + 20, contr, 0x0000FFFF);
   	draw_square(contr->p_x , contr->p_y , contr->p_x + 20, contr->p_y + 20, contr, 0x0000FFFF);
   	print_image(contr,0,0);
   //	mlx_put_image_to_window(contr->mlx_ptr, contr->win_ptr, (contr->img).img, 0, 0);
   //	mlx_destroy_image(contr->mlx_ptr, contr->img.img);
	return (0);
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
	int test[4] = {200,200,0,0};

	t_contr *contr;
	contr = (t_contr *)params;
	if (key == 13)
	{
		contr->p_y -= 0.05f;
	}
	else if (key == 1)
	{
		contr->p_y += 0.05f;
	}
	else if (key == 0)
	{
		contr->p_x -= 0.05f;
	}
	else if (key == 2)
	{
		contr->p_x += 0.05f;
	}
	else if(key == 53)
		exit(0);
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

	draw_square(x, y, x + 200 , y + 100, (t_contr *)params, WHITE);
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

	move_speed = 3.5f;
	contr = (t_contr*)param;
	if (key == 13)
		contr->p_y -= move_speed;
	else if (key == 1)
		contr->p_y += move_speed;
	else if (key == 0)
		contr->p_x -= move_speed;
	else if (key == 2)
		contr->p_x += move_speed;
	if(key == 53)
		exit(0);
	return 0;
}
int key_release(int key,void *param)
{
	printf("KEYUP = %d \n",key );
	return 0;
}

int main()
{
	t_contr contr;
	
	void *mlx_ptr;
	void *win_ptr;

	void *img;

	contr.res_w = 640;
	contr.res_h = 480;

	contr.dir_x = -1;
	contr.dir_y = 0;

	contr.planeX = 0;
	contr.planeY = 0.66;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, contr.res_w, contr.res_h, "test");
	
	t_img image;


	image.img = mlx_new_image(mlx_ptr, 640, 480);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;


	contr.mlx_ptr = mlx_ptr;
	contr.win_ptr = win_ptr;

//	void (*fun_ptr)(void*) = &voidprocess; 

	mlx_do_key_autorepeaton(mlx_ptr);
	mlx_key_hook(win_ptr, process_key, (void *)&contr);
	mlx_mouse_hook (win_ptr, process_mouse, (void *)&contr);
	mlx_loop_hook(mlx_ptr, voidprocess, (void *)&contr);
	//mlx_expose_hook(win_ptr,sample, 0 );
	mlx_hook(win_ptr,17,0, close_win, (void *)&contr);
	mlx_hook(win_ptr,2,0, key_press, (void *)&contr);
	mlx_hook(win_ptr,3,0, key_release, (void *)&contr);
	load_map("map/1.mp", &contr);
	//printf("int = %d \n",color );
	
	//mlx_do_sync(mlx_ptr);
	contr.pas_x = contr.res_w / contr.map_w;
	contr.pas_y = contr.res_h / contr.map_w;
	
	contr.value = contr.p_x * contr.pas_x;


	//mlx_string_put(mlx_ptr, win_ptr, 0, 0, RED, "Hello world");
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, blanc);
	//mlx_pixel_put(mlx_ptr, win_ptr,  5,  7, 250);
	// /mlx_string_put()
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
	free(win_ptr);
	return 0;
}