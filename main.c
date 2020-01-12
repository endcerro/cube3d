/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 06:45:59 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/12 12:13:43 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header/header.h"

//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

int draw_square(double x_0, double y_0, double x_e, double y_e, t_contr *contr, int color)
{
	draw_line(x_0,y_0, x_e, y_0, contr, color);
	draw_line(x_0,y_0, x_0, y_e, contr, color);
	draw_line(x_e,y_0, x_e, y_e, contr, color);
	draw_line(x_0,y_e, x_e, y_e, contr, color);
	return 0;
}

double correct_angle(double angle)
{
	printf("corrected %f \n",ft_abs_double(angle - 360));
	return ft_abs_double(angle - 360);
}

double correct_angle_d(double angle)
{
	printf("corrected D%f \n",ft_abs_double(angle +270));
	return ft_abs_double(angle +270);
}


void dda(t_contr *contr)
{

	double angle = contr->angle;
	double pos_x = ((contr->p_x * contr->map_w) / contr->res_w);
	//WARNING MAP_W
	double pos_y = ((contr->p_y * contr->map_w) / contr->res_h);
	double Ya = 1;
	double Xa;

	double fov = 60.0;

	
	double direct_x;
	double direct_y;
	//int up;
	//fmod(((M_PI - (M_PI / 2) - angle) * (180/M_PI)),(2.0*M_PI));
	// up = -1; 
	// if(sin(angle) >= 0)
	// 	up = 1;
	double val;
	Xa = 1 / tan(angle);
	//Ya = Xa / tan(angle);
	//printf("Ya = %f", Ya);
	//	double dist_x =  pos_x - (int)(contr->p_x * contr->map_w);
	double dist_y = ft_abs_double(pos_y - (int)pos_y);
	printf("dist_y = %f\n", dist_y); //OK
	double dist_x = 1- ft_abs_double(pos_x - (int)pos_x);
	printf("dist_x = %f\n", dist_x); //OK



	//printf("Known angle = %f\n", fmod(angle , 2*M_PI)* (180/M_PI));
	//printf("Last angle = %f\n", fmod(((M_PI - (M_PI / 2) - angle) * (180/M_PI)),(2.0*M_PI)));
	
	double angle_c = fmod(angle,2*M_PI) * (180/M_PI); //* (180/M_PI);
	//double last_angle = (90 - angle*(180/M_PI));
	//if(last_angle < 0)
	

	//	last_angle = (angle*(180/M_PI) - 90);
	//direct_x = cos(angle_c_i);
	printf("Angle connu C: %f || rad %f: \n", angle_c, angle_c / (180.0/M_PI));
	double angle_c_i = correct_angle(fmod(angle,2*M_PI) * (180/M_PI));
	double dist_x_pixel;
	double dist_y_pixel;
	direct_x = cos(angle_c_i / (180.0 / M_PI));
	direct_y = sin(angle_c_i/ (180.0 / M_PI));
	if(direct_x < 0.0)
	{
		direct_x = -1.0;
		dist_x = ft_abs_double((int)pos_x - pos_x);
	}
	else if (direct_x != 0)
	{
		direct_x = 1.0;
	}

	if(direct_y < 0.0)
	{
		direct_y = -1.0;
		dist_y = 1 - dist_y;
	}
	else if (direct_y != 0.0)
	{
		direct_y = 1.0;
	}

	dist_x_pixel = ft_abs_double(dist_x * (contr->res_w / contr->map_w));
	printf("dist_x_pixel = %f\n", dist_x_pixel); //OK

	dist_y_pixel = ft_abs_double(dist_y * (contr->res_h / contr->map_w));
	printf("dist_y_pixel = %f\n", dist_y_pixel); //OK

	//((dist_x * contr->map_w) / contr->res_w)
	draw_line( contr->p_x, contr->p_y, (contr->p_x + dist_x_pixel * direct_x)  , contr->p_y, contr, 0x00FF0000);
	draw_line( contr->p_x, contr->p_y, contr->p_x , contr->p_y - dist_y_pixel * direct_y , contr, 0x00FF0000);


	printf("Direction x = %f y = %f \n", direct_x, direct_y);
	//double angle_cc = correct_angle(angle_c);
	

	//double last_angle = (90 - angle*(180/M_PI));
	//double last_anglec = 180 - 90 - angle_cc;
	
	//if(last_anglec < 0)
	//	last_anglec += 360;
	//printf("Last anglec = %f\n", last_anglec);

	
	//printf("Last angle = %f\n", last_angle);
	//correct_angle_d(last_anglec);




	//double dist_x =  dist_y  / tan(M_PI/2 - (correct_angle(angle_c)/(180/M_PI)));
	//printf("dist_x = %f\n", dist_x);
	//double dist_x =  modf(pos_x,&val);
	// double hypoth_first =  
	//printf("REAL pos x = %f y = %f\n",((contr->p_x * contr->map_w) / contr->res_w), (contr->p_y * contr->map_w) / contr->res_h );
	//printf("X = %f Y = %f\n",pos_x, pos_y );
	//printf("Xa = %f\n", Xa);
	//printf("dist_y = %f\n", dist_y);
	//printf("dist_x = %f\n", dist_x);
	
	//my_mlx_pixel_put(contr, contr->p_x + dist_x, contr->p_y + dist_y, 0x00FFFF00);

	
}

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
   	draw_line(contr->p_x   , contr->p_y  , (contr->p_x + (contr->dir_x * 100.0)), 
   		(contr->p_y +  (contr->dir_y * 100.0)), contr, 0x0000FF00);
   	dda(contr);
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

	move_speed = 3.5;
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


	//printf("pos x = %f y = %f\n",contr->p_x, contr->p_y );
	//ATTENTION CODE EXPLOSIF
	printf("REAL pos x = %d y = %d\n",(int)((contr->p_x * contr->map_w) / contr->res_w), (int)(contr->p_y * contr->map_w) / contr->res_h );
	//printf("key = %d \n",key );

	contr->value = contr->p_x * contr->pas_x;
	//printf("REAL pos x = %d\n",contr->value);

	if(contr->angle >= 2 * M_PI)
		contr->angle -= 2 * M_PI;
	if(contr->angle <= 0)
		contr->angle += 2 * M_PI;

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