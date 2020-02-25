/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:26:15 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/25 23:43:07 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"

int mouse_(int btn, int x, int y, void *params)
{
	t_contr *contr;
	int 	ring;

	ring = 0;
	btn = 0;
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
	// if(contr->enn_id <= -1)
	// 	return;
	// printf("here %d\n",contr->enn_id);
	contr->sprites[contr->enn_id].y += (contr->pos.y - contr->sprites[contr->enn_id].y) / 180;
	contr->sprites[contr->enn_id].x += (contr->pos.x - contr->sprites[contr->enn_id].x) / 180; 
	contr->sprites[contr->enn_id].texture = contr->textures[contr->text_nb - 2];

	t_vp dist;

	dist.x = fabs(contr->pos.x - contr->sprites[contr->enn_id].x);
	dist.y = fabs(contr->pos.y - contr->sprites[contr->enn_id].y);
	if(dist.y < 0.75 && dist.x < 0.75 )
	{
		printf("dist x = %f dist y = %f \n",dist.x, dist.y );
		contr->hp -= 10;
		printf("PLAYER HIT\n");
	}
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
			// if(i > 10 && j > 10 && i < len.x - 10 && j < len.y - 10 && contr->dark_mode == 1)
				// mlx_pixel_put(contr->mlx, contr->win_ptr,start.x + j, start.y + i, 0x00000000);
			// else
				mlx_pixel_put(contr->mlx, contr->win_ptr,start.x + j, start.y + i, color);			
		}
	}

}

void draw_square_i(t_contr *contr, t_vpi start, t_vpi len, int color)
{
	int i;
	int j;
	
	i = 0;
	while(++i < len.y)
	{
		j = 0;
		while(++j < len.x)
			p_px(contr, start.x + j, start.y + i, color);			
	}
}
void draw_drk_b(t_contr *contr)
{
	t_vpi t;
	t.x = 250;
	t.y = 260;
	t_vpi t2;
	t2.x = 40;
	t2.y = 40;
	draw_square(contr, t, t2, 0x00FFFFFF);
	if(contr->dark_mode == 1)
	{	
		t.x += 10;
		t.y += 10;
		t2.x -= 20;
		t2.y -= 20;
		draw_square(contr, t, t2, 0x00000000);
	}
}
void show_sett(t_contr *contr)
{
	t_vpi xy;
	t_vpi start;
	int width;
	int i;

	xy = set_vpi(0,0);
	i = -1;
	start = set_vpi(70,90);
	while((xy.x = 0) || ++i < 3)
	{
		width = contr->sett.rot_speed * 23;
		if(i == 0)
			width = contr->sett.fov * 23;		
		else if (i == 1)
			width = contr->sett.move_speed * 23;
		while(++xy.x < width)
		{	
			xy.y = -1;
			while(xy.y++ < 20)
				mlx_pixel_put(contr->mlx, contr->win_ptr,start.x + xy.x, 
					start.y + xy.y, 0x00FFFFFF);
		}
		start.y += 60;
	} 
	draw_drk_b(contr);
}
void			print_image2(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx, contr->win_ptr);
	
	mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	(contr->textures[8]).texture.img, x, y);
	show_sett(contr);
	mlx_destroy_image(contr->mlx, contr->img.img);
	contr->img.img = mlx_new_image(contr->mlx, contr->res.x , contr->res.y);
	contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp),
		&(contr->img.length), &(contr->img.endian));
}

void draw_hp(t_contr *contr)
{
	t_vpi t;
	t.y = contr->res.y - 100;
	t.x = 10;
	t_vpi t2;
	t2.x = 0.25 * 1000;
	t2.y = 40;
	draw_square_i(contr, t, t2, 0x00000000);
	t2.x = 0.25 * contr->hp;
	if(contr->hp > 750)
		draw_square_i(contr, t, t2, 0x0000FF00);
	else if(contr->hp > 500)
		draw_square_i(contr, t, t2, 0x00FFFF00);
	else if(contr->hp > 250)
		draw_square_i(contr, t, t2, 0x00FFA500);
	else
		draw_square_i(contr, t, t2, 0x00FF0000);
	if(contr->hp == 0)
		close_(contr, 0);
}
void menu_mode(t_contr *contr)
{
	if(contr->res.y < 400 || contr->res.x < 400)
	{
		write(1,"MENU AVAILABLE AT THIS RESOLUTION",33);
		contr->menu_mode = 0;
		return;
	}
	print_image2(contr, 0,0);
}



void draw_wpn(t_contr *contr)
{
	t_vpi pos;
	t_vpi draw_p;
	t_vp  stp;
	int spr_id;
	int clr;

	spr_id = (contr->atk_frame > 1) ? 1 : 0;
	pos = set_vpi(0,0);
	draw_p = set_vpi(0,	contr->res.y - contr->res.y / 2 - 1);
	stp.x = 1.0 * (contr->res.x / 2 ) / contr->weapons[spr_id].w;
	stp.y = 1.0 * (contr->res.y / 2 ) / contr->weapons[spr_id].h;
	while(++draw_p.y < contr->res.y)
	{
		pos.x = 0;
		draw_p.x = contr->res.x - contr->res.x / 2 - 1;
		while(++draw_p.x < contr->res.x)
		{
			clr = g_px(contr->weapons[spr_id], pos.x++ / stp.x, pos.y / stp.y);
			if(clr != 0x00000000)
				p_px(contr, draw_p.x, draw_p.y, clr);
		}
		pos.y++;
	}
	if(contr->atk_frame > 0)
		contr->atk_frame--;
}

#ifdef BONUS
int loop_(void *params)
{
	t_contr *contr;

	contr = (t_contr*)params;
	if(contr->menu_mode == 0)
	{
		dda((t_contr*)params);
		move_spr(params);
		handle_keys((t_contr*)params);
		draw_minmap((t_contr*)params);
		draw_hp((t_contr*)params);
		draw_wpn((t_contr*)params);
		print_image((t_contr*)params,0,0);
	}
	else
		menu_mode(contr);
	
	return (0);
}
#else
int loop_(void *params)
{
	dda((t_contr*)params);
	handle_keys((t_contr*)params);
	print_image((t_contr*)params,0,0);
	return (0);
}
#endif
int close_(t_contr *contr, char *message)
{
  //  t_contr *contr = (t_contr*)contr;
  	write(1, message, ft_strlen(message));
	mlx_destroy_image(contr->mlx, (contr->textures[8]).texture.img);
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


void load_wpns(t_contr *contr)
{
	t_text *texture;
	
	texture = &(contr->weapons[0]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, "textures/attack_idle.xpm", &texture->w, &texture->h);
	if(texture->texture.img == 0)
		close_(contr, "ERROR TEXTURE NOT FOUND\n");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->texture.bpp), &(texture->texture.length), &(texture->texture.endian));
	texture = &(contr->weapons[1]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, "textures/attack_on.xpm", &texture->w, &texture->h);
	if(texture->texture.img == 0)
		close_(contr, "ERROR TEXTURE NOT FOUND\n");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->texture.bpp), &(texture->texture.length), &(texture->texture.endian));
	// printf("texture n: %d w= %d h= %d\n",index, texture->w, texture->h);
	// contr->text_nb++;
}

int main(int argc, char **argv)
{

	// strlen(NULL);
	t_contr contr;
	
	void *mlx;
	void *win_ptr;

	mlx = mlx_init();
	contr.mlx = mlx;
	contr.text_nb = 0;
	contr.win_ptr = 0;
	contr.enn_id = -1;
	contr.sprites_nb = 0;
	// contr.dir.x = -1;
 // 	contr.dir.y = 0;
	
	

	if(argc < 2)
		close_(&contr, "Please state the path of the map");
	if(argc == 3 && ft_strcmp(argv[2], "--save"))
		contr.screen = 1;
	else
		contr.screen = 0;
	load_cub(argv[1], &contr);	

	// contr.plane.y = 0.66;
	win_ptr = mlx_new_window(mlx, contr.res.x, contr.res.y, "cub3d");
	

	
	t_img image;
	image.img = mlx_new_image(mlx, contr.res.x , contr.res.y);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;
	contr.sett.move_speed = 5;
	contr.sett.rot_speed = 5;
	contr.sett.fov = 5;
	contr.atk_frame = 0;
	contr.hp = 1000;
	contr.win_ptr = win_ptr;
  	contr.menu_mode = 0;
	contr.dark_mode = 0;

	init_keys(&contr);

	texture_loadr("textures/new_floor.xpm", &contr, -1);
	texture_loadr("textures/TOFIX.xpm", &contr, -1);
	texture_loadr("textures/pghost.xpm", &contr, -1);
	texture_loadr("textures/MENU.xpm", &contr, -1);
	load_wpns(&contr);
	// texture_loadr("textures/MENU.xpm", &contr, -1);
	// texture_loadr("textures/MENU.xpm", &contr, -1);

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
