/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:43:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 20:38:34 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void			print_image(t_contr *contr, int x, int y)
{
	mlx_clear_window(contr->mlx, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx, contr->win_ptr,
	(contr->img).img, x, y);
	if (contr->screen == 1)
	{
		get_screenshot(contr);
		contr->screen = 0;
	}
	mlx_destroy_image(contr->mlx, contr->img.img);
	contr->img.img = mlx_new_image(contr->mlx, contr->res.x, contr->res.y);
	contr->img.addr = mlx_get_data_addr(contr->img.img, &(contr->img.bpp),
		&(contr->img.length), &(contr->img.endian));
}

void			p_px(t_contr *contr, int x, int y, int color)
{
	char	*dst;
	t_img	img;

	img = contr->img;
	dst = img.addr + (y * img.length + x * (img.bpp / 8));
	*(unsigned int*)dst = (unsigned int)color;
}

unsigned int	g_px(t_text tx, int x, int y)
{
	return (*(unsigned int*)(tx.texture.addr +
		(y * tx.texture.length + x * (tx.texture.bpp / 8))));
}

unsigned int	g_vpx(t_text tx, t_vpi pos)
{
	return (*(unsigned int*)(tx.texture.addr +
		(pos.y * tx.texture.length + pos.x * (tx.texture.bpp / 8))));
}

void			draw_square_i(t_contr *contr, t_vpi start, t_vpi len, int color)
{
	int i;
	int j;

	i = 0;
	while (++i < len.y)
	{
		j = 0;
		while (++j < len.x)
			p_px(contr, start.x + j, start.y + i, color);
	}
}
