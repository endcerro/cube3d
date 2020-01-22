/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 06:45:59 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 04:09:36 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header/header.h"

//gcc -I /usr/local/include main.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

int mouse_(int btn, int x, int y, void *params)
{
	return (0);
}


int loop_(void *params)
{
	dda((t_contr*)params);
	print_image((t_contr*)params,0,0);
	return (0);
}


int close_(void *param)
{
    t_contr *contr = (t_contr*	)contr;
  
    free(contr->mlx);
	free(contr->win_ptr);
    exit(0);
    return(0);
}

int main()
{
	t_contr contr;
	
	void *mlx;
	void *win_ptr;
	
	void *img;

	contr.res_h = 480;
	contr.res_w = 640;

	mlx = mlx_init();
	win_ptr = mlx_new_window(mlx, contr.res_w, contr.res_h, "cub3d");
	
	t_img image;
	image.img = mlx_new_image(mlx, contr.res_w, contr.res_w);
	image.addr =  mlx_get_data_addr(image.img, &(image.bpp), &(image.length), &(image.endian));

	contr.img = image;
	contr.mlx = mlx;
	contr.win_ptr = win_ptr;



	contr.pos.x = 3;
	contr.pos.y = 3;  //x and y start position
 	
 	contr.dir.x = -1;
 	contr.dir.y = 0; //initial direction vector
  	
  	contr.plane.x = 0;
	contr.plane.y = 1; //the 2d raycaster version of camera plane







	load_map("map/1.mp", &contr);

	mlx_do_key_autorepeaton(mlx);
	mlx_hook(win_ptr,17,0, close_, (void *)&contr);
	mlx_hook(win_ptr,2,0, key_press, (void *)&contr);
	//mlx_key_hook(win_ptr, process_key, (void *)&contr);
	//mlx_mouse_hook (win_ptr, process_mouse, (void *)&contr);
	mlx_loop_hook(mlx, loop_, (void *)&contr);
	//mlx_expose_hook(win_ptr,sample, 0 );
	//mlx_hook(win_ptr,3,0, key_release, (void *)&contr);
	
	mlx_loop(mlx);
	
	return 0;
}