/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 06:45:59 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/17 15:35:41 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"
#include <pthread.h> 

// int mouse_(int btn, int x, int y, void *params)
// {
// 	return (0);
// }

void move_spr(t_contr *contr)
{
	contr->sprites[contr->sprites_nb - 1].y += (contr->pos.y - contr->sprites[contr->sprites_nb - 1].y) / 180;
	contr->sprites[contr->sprites_nb - 1].x += (contr->pos.x - contr->sprites[contr->sprites_nb - 1].x) / 180; 
	contr->sprites[contr->sprites_nb - 1].texture = contr->textures[contr->text_nb - 1];
}
int loop_(void *params)
{
	dda((t_contr*)params);
	#ifdef BONUS
	move_spr(params);
	#endif
	handle_keys((t_contr*)params);
	print_image((t_contr*)params,0,0);
	return (0);
}


int close_(t_contr *contr, char *message)
{
  //  t_contr *contr = (t_contr*)contr;
  	write(1, message, ft_strlen(message));
    free(contr->mlx);
	free(contr->win_ptr);
    exit(0);
    return(0);
}

void texture_loadr(char *path, t_contr *contr)
{
	
	t_text *texture;
	texture = &(contr->textures[contr->text_nb]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, path, &texture->w, &texture->h);
	if(texture->texture.img == 0)
		close_(contr, "ERROR TEXTURE NOT FOUND\n");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->texture.bpp), &(texture->texture.length), &(texture->texture.endian));
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



int main()//int argc, char **argv)
{
	t_contr contr;
	
	void *mlx;
	void *win_ptr;

	mlx = mlx_init();
	contr.mlx = mlx;
	contr.text_nb = 0;
	contr.win_ptr = 0;
	
	contr.dir.x = -1;
 	contr.dir.y = 0;
	
	contr.plane.x = 0;
	contr.plane.y = 0.66;
	load_cub("map/sample.cub", &contr);	

	win_ptr = mlx_new_window(mlx, contr.res_w, contr.res_h, "cub3d");
	
	
	t_img image;
	image.img = mlx_new_image(mlx, contr.res_w, contr.res_w);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;

	contr.win_ptr = win_ptr;

 	contr.screen = 0;	

  	
  	
	contr.dark_mode = 0;
	init_keys(&contr);

	texture_loadr("textures/wood.xpm", &contr);
	

	texture_loadr("textures/mossy.xpm", &contr);
	texture_loadr("textures/yoshi.xpm", &contr);
	
	mlx_do_key_autorepeaton(mlx);
	mlx_hook(win_ptr,17,0, close_, (void *)&contr);
	mlx_hook(win_ptr,2,0, key_press, (void *)&contr);
	mlx_loop_hook(mlx, loop_, (void *)&contr);
	mlx_hook(win_ptr,3,0, key_release, (void *)&contr);
	
	mlx_loop(mlx);
	
	return 0;
}
