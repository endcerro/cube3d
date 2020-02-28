/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:43:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 02:59:58 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

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

void			draw_square(t_contr *contr, t_vpi start, t_vpi len, int color)
{
	int i;
	int j;

	i = 0;
	while (++i < len.y)
	{
		j = 0;
		while (++j < len.x)
		{
			mlx_pixel_put(contr->mlx, contr->win_ptr, start.x + j,
					start.y + i, color);
		}
	}
}
