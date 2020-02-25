/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:27:55 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/25 18:28:12 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	draw_minmap(t_contr *contr)
{
	t_vpi draw_p;

	draw_p.x = 0;
	draw_p.y = 0;

	t_vpi width;
	t_vpi width2;



	if(contr->map_w > contr->map_h)
	{	
		width.x = contr->res_h / contr->map_w / 5;
		width.y = contr->res_h / contr->map_w / 5;
	}
	else
	{
		width.x = contr->res_w / contr->map_h / 5;
		width.y = contr->res_w / contr->map_h / 5;
	}


	width2.x = width.x / 2.0;
	width2.y = width.y / 2.0;

	t_vpi p;
	p.x = 0;
	p.y = 0;
	while(p.y < contr->map_h)
	{
		p.x = 0;
		draw_p.x = 0;
		while(p.x < contr->map_w)
		{
			if(contr->map[p.y][p.x] == '1')
				draw_square_i(contr, draw_p, width, 0x00FFFFFF);
			if(contr->map[p.y][p.x] == '2')
				draw_square_i(contr, draw_p, width2, 0x0000FF00);
			draw_p.x += width.x;
			p.x++;
		}
		draw_p.y += width.y;
		p.y++;
	}
	t_vpi test;
	test.x = (contr->pos.x - 0.25) * width.x;
	test.y = (contr->pos.y - 0.25) * width.y;
	width.x *= 0.5;
	width.y *= 0.5;
	
	draw_square_i(contr, test, width, 0x00FF0000);
}
