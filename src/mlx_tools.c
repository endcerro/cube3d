/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 02:44:31 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 16:07:06 by edal--ce         ###   ########.fr       */
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
		close_(contr, 0);
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

void			texture_loadr(char *path, t_contr *contr, int index)
{
	t_text *texture;

	if (index == -1)
		index = contr->tx_nb;
	texture = &(contr->textures[index]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, path, &texture->w,
		&texture->h);
	if (texture->texture.img == 0)
		close_(contr, "Error\nTEXTURE NOT FOUND");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->
		texture.bpp), &(texture->texture.length), &(texture->texture.endian));
	contr->tx_nb++;
}

int				close_hook(t_contr *contr)
{
	close_(contr, 0);
	return (0);
}
