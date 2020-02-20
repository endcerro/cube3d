/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 06:45:59 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/20 10:16:27 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"
#include <pthread.h> 

int mouse_(int btn, int x, int y, void *params)
{
	t_contr *contr;

	int ring = 0;
	contr = (t_contr*)params;
	if(contr->menu_mode)
	{
		if(x >= 325 && x <= 345)
		{
			if(y >= 90 && y <= 110 && contr->sett.fov < 10 && (ring = 1))
			{
				change_fov(contr, -1);
				contr->sett.fov++;
			}
			else if(y >= 150 && y <= 170 && contr->sett.move_speed < 10&& (ring = 1))
				contr->sett.move_speed++;
			else if(y >= 210 && y <= 230 && contr->sett.rot_speed < 10&& (ring = 1))				
				contr->sett.rot_speed++;
		}
		else if(x >= 30 && x <= 50)
		{
			if(y >= 90 && y <= 110 && contr->sett.fov > 1&& (ring = 1))
			{
				change_fov(contr, 1);
				contr->sett.fov--;
			}
			else if(y >= 150 && y <= 170 && contr->sett.move_speed > 1&& (ring = 1))	
				contr->sett.move_speed--;
			else if(y >= 210 && y <= 230 && contr->sett.rot_speed > 1&& (ring = 1))				
				contr->sett.rot_speed--;
		}
		else if(y >= 355 && y <= 385)
		{
			if(x >= 35 && x <= 115 && (ring = 1))	
				contr->menu_mode = 0;
			if(x >= 289 && x <= 358 && (ring = 1))
				close_(contr,0);	
		}
		else if(y >= 260 && y <= 300)
		{
			if(x >= 250 && x <= 290 && (ring = 1))	
				contr->dark_mode = !contr->dark_mode;
		}
		if(ring)
			write(1,"\a",1);
	}
 	printf("x = %d, y = %d\n",x, y );
 	return (0);
}

void move_spr(t_contr *contr)
{
	contr->sprites[contr->sprites_nb - 1].y += (contr->pos.y - contr->sprites[contr->sprites_nb - 1].y) / 180;
	contr->sprites[contr->sprites_nb - 1].x += (contr->pos.x - contr->sprites[contr->sprites_nb - 1].x) / 180; 
	contr->sprites[contr->sprites_nb - 1].texture = contr->textures[contr->text_nb - 1];
}

void draw_square(t_contr *contr, t_vpi start, t_vpi len, int color)
{

	int i;
	int j;
	i = 0;
	while(++i < len.y)
	{
		j = 0;
		while(++j < len.x)
		{
			if(i > 10 && j > 10 && i < len.x - 10 && j < len.y - 10 && contr->dark_mode == 1)
				mlx_pixel_put(contr->mlx, contr->win_ptr,start.x + j, start.y + i, 0x00000000);
			else
				mlx_pixel_put(contr->mlx, contr->win_ptr,start.x + j, start.y + i, 0x00FFFFFF);			
		}
	}

}

void show_bars(t_contr *contr)
{
	int x = 0;
	int y = 0;

	int height = 20;
	int width = 230;
	int starty = 90;
	int startx = 70;
	width = contr->sett.fov * 23;
	while(++x < width)
	{
		y = -1;
		while(y++ < height)
		{
			mlx_pixel_put(contr->mlx, contr->win_ptr,startx + x, starty + y, 0x00FFFFFF);	
		}
	}
	starty += 60;
	width = contr->sett.move_speed * 23;
	// width = contr->sett.move_speed * 23;
	x = 0;
	while(++x < width)
	{
		y = -1;
		while(y++ < height)
		{
			mlx_pixel_put(contr->mlx, contr->win_ptr,startx + x, starty + y, 0x00FFFFFF);	
		}
	}
	starty += 60;
	width = contr->sett.rot_speed * 23;
	x = 0;
	while(++x < width)
	{
		y = -1;
		while(y++ < height)
		{
			mlx_pixel_put(contr->mlx, contr->win_ptr,startx + x, starty + y, 0x00FFFFFF);	
		}
	}
	t_vpi t;
	t.x = 250;
	t.y = 260;
	t_vpi t2;
	t2.x = 40;
	t2.y = 40;

	draw_square(contr, t, t2, 0x00FFFFFF);

//	draw_square(contr, t, t2, 0x00FFFFFF);
}
void			print_image2(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx, contr->win_ptr);
	
	mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	(contr->textures[8]).texture.img, x, y);
	show_bars(contr);
	if (contr->screen == 1)
	{
		get_screenshot(contr);
		contr->screen = 0;
	}
	// mlx_string_put(contr->mlx, contr->win_ptr, 0, 0, 0x00FF0000, "120");
	// mlx_destroy_image(contr->mlx, (contr->textures[8]).texture.img);
	// contr->menu_mode = 0;
	mlx_destroy_image(contr->mlx, contr->img.img);
	contr->img.img = mlx_new_image(contr->mlx, contr->res_w , contr->res_h );
	contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp),
		&(contr->img.length), &(contr->img.endian));
}


void menu_mode(t_contr *contr)
{
	// print_image(contr,0,0);

	// mlx_destroy_image(contr->mlx, contr->img.img);
	// mlx_clear_window(contr->mlx, contr->win_ptr);
	if(contr->res_h < 400 || contr->res_w < 400)
	{
		write(1,"MENU AVAILABLE AT THIS RESOLUTION",33);
		contr->menu_mode = 0;
		return;
	}
	
	// mlx_clear_window(contr->mlx, contr->win_ptr);
	print_image2(contr, 0,0);
	

// mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	// (contr->textures[8]).texture.img, 20, 20);
	// char *cache;
	// free(contr->win_ptr);
	// mlx_destroy_image(contr->mlx, contr->img.img);
	// mlx_clear_window(contr->mlx, contr->win_ptr);
	// contr->img.img = mlx_new_image(contr->mlx, contr->res_w , contr->res_h );
	// contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp), &(contr->img.length), &(contr->img.endian));
	
	// cache = ft_itoa(contr->sett.fov);
	// mlx_string_put(contr->mlx, contr->win_ptr, contr->res_w / 3 , 100, 0x00FF0000, "FOV : ");
	// mlx_string_put(contr->mlx, contr->win_ptr, contr->res_w / 3 + 200 , 100, 0x00FF0000, cache);
	// free(cache);
	// mlx_string_put(contr->mlx, contr->win_ptr, contr->res_w / 3 , 200, 0x00FF0000, "MOVE_SPEED : ");
	// mlx_string_put(contr->mlx, contr->win_ptr, contr->res_w / 3 , 300, 0x00FF0000, "ROTATION_SPEED : ");
}
int loop_(void *params)
{
	t_contr *contr;

	contr = (t_contr*)params;
	if(contr->menu_mode == 0)
	{
		dda((t_contr*)params);
		// #ifdef BONUS
		// //move_spr(params);
		// #endif
		handle_keys((t_contr*)params);
		print_image((t_contr*)params,0,0);
	}
	else
	{
		menu_mode(contr);
	}
	
	return (0);
}



int close_(t_contr *contr, char *message)
{
  //  t_contr *contr = (t_contr*)contr;
  	write(1, message, ft_strlen(message));
	mlx_destroy_image(contr->mlx, (contr->textures[8]).texture.img);
  	// for(int i = 0; i < 1; i++)
  	// {
  	// 	mlx_destroy_image(contr->mlx, contr->sprites[i].texture.texture.img);	
  	// }
  	// mlx_destroy_image(contr->mlx, contr->sprites[0].texture.texture.img);
  	// mlx_destroy_image(contr->mlx, contr->img.img);
  	// mlx_destroy_image(contr->mlx, contr->img.img);
  	// mlx_destroy_image(contr->mlx, contr->img.img);
  	// mlx_destroy_image(contr->mlx, contr->img.img);
  	// mlx_destroy_image(contr->mlx, contr->img.img);
    free(contr->mlx);
	free(contr->win_ptr);


	system("leaks a.out");
    exit(0);
    return(0);
}

void texture_loadr(char *path, t_contr *contr, int index)
{
	if(index == -1)
		index = contr->text_nb;
	t_text *texture;
	texture = &(contr->textures[index]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, path, &texture->w, &texture->h);
	if(texture->texture.img == 0)
		close_(contr, "ERROR TEXTURE NOT FOUND\n");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->texture.bpp), &(texture->texture.length), &(texture->texture.endian));
	printf("texture n: %d w= %d h= %d\n",index, texture->w, texture->h);
	contr->text_nb++;
}

void init_keys(t_contr *contr)
{
	contr->key.w = 0;
	contr->key.a = 0;
	contr->key.s = 0;
	contr->key.d = 0;
	contr->key.q = 0;
	contr->key.e = 0;
}

int checksave(char *str)
{
	int i = 0;
	char *comp = "-save";
	while(str[i])
	{
		if(str[i] == comp[i])
			i++;
		else
		{
			printf("NN\n");
			return 0;
		}
	}
	if(str[i] == 0 && comp[i] == 0)
	{
		printf("GOOD\n");
		return 1;
	}
	else{
		printf("NN\n");
		return 0;
	}
}


int main(int argc, char **argv)
{

	t_contr contr;
	
	void *mlx;
	void *win_ptr;

	mlx = mlx_init();
	contr.mlx = mlx;
	contr.text_nb = 0;
	contr.win_ptr = 0;
	
	// contr.dir.x = -1;
 // 	contr.dir.y = 0;
	
	

	if(argc < 2)
		close_(&contr, "Please state the path of the map");
	if(argc == 3 && ft_strcmp(argv[2], "-save"))
		contr.screen = 1;
	else
		contr.screen = 0;
	load_cub(argv[1], &contr);	

	// contr.plane.y = 0.66;
	win_ptr = mlx_new_window(mlx, contr.res_w, contr.res_h, "cub3d");
	
	
	t_img image;
	image.img = mlx_new_image(mlx, contr.res_w , contr.res_h);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;
	contr.sett.move_speed = 5;
	contr.sett.rot_speed = 5;
	contr.sett.fov = 5;

	contr.win_ptr = win_ptr;
  	contr.menu_mode = 0;
	contr.dark_mode = 0;
	init_keys(&contr);

	texture_loadr("textures/new_floor.xpm", &contr, -1);
	texture_loadr("textures/TOFIX.xpm", &contr, -1);
	texture_loadr("textures/yoshi.xpm", &contr, -1);
	texture_loadr("textures/MENU.xpm", &contr, -1);
	mlx_do_key_autorepeaton(mlx);
	mlx_hook(win_ptr,17,0, close_, (void *)&contr);
	mlx_hook(win_ptr,2,0, key_press, (void *)&contr);
	mlx_hook(win_ptr,3,0, key_release, (void *)&contr);
	mlx_mouse_hook(win_ptr, mouse_, (void *)&contr);

	mlx_loop_hook(mlx, loop_, (void *)&contr);
	mlx_loop(mlx);
	// mlx_destroy_image(contr.mlx, (contr.textures[8]).texture.img);
	close_(&contr, 0);
	//system("leaks a.out");
	return 0;
}
