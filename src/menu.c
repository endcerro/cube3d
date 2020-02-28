/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:57:52 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 03:00:41 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	show_sett(t_contr *contr)
{
	t_vpi	xy;
	t_vpi	start;
	int		width;
	int		i;

	xy = set_vpi(0, 0);
	i = -1;
	start = set_vpi(70, 90);
	while ((xy.x = 0) || ++i < 3)
	{
		width = contr->sett.rot_speed * 23;
		if (i == 0)
			width = contr->sett.fov * 23;
		else if (i == 1)
			width = contr->sett.move_speed * 23;
		while (++xy.x < width)
		{
			xy.y = -1;
			while (xy.y++ < 20)
				mlx_pixel_put(contr->mlx, contr->win_ptr, start.x + xy.x,
					start.y + xy.y, 0x00FFFFFF);
		}
		start.y += 60;
	}
	draw_drk_b(contr);
}

void	print_menu(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	(contr->textures[8]).texture.img, x, y);
	show_sett(contr);
	mlx_destroy_image(contr->mlx, contr->img.img);
	contr->img.img = mlx_new_image(contr->mlx, contr->res.x, contr->res.y);
	contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp),
		&(contr->img.length), &(contr->img.endian));
}

void	menu_mode(t_contr *contr)
{
	if (contr->res.y < 400 || contr->res.x < 400)
	{
		write(1, "MENU NOT AVAILABLE AT THIS RESOLUTION", 33);
		contr->menu_mode = 0;
		return ;
	}
	print_menu(contr, 0, 0);
}
