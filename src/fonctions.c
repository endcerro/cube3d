/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:43:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/18 17:02:33 by edal--ce         ###   ########.fr       */
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
	contr->img.img = mlx_new_image(contr->mlx, contr->res_w, contr->res_h);
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

// void 			draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color)
// {
	
// 	double x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	
// 	dx = x2 - x1;
// 	dy = y2 - y1;
	
// 	dx1 = ft_abs_double(dx);
// 	dy1 = ft_abs_double(dy);
	
// 	px = 2 * dy1 - dx1;
// 	py = 2 * dx1 - dy1;
	
// 	if (dy1 <= dx1)
// 	{
// 		if (dx >= 0)
// 		{
// 			x = x1; 
// 			y = y1; 
// 			xe = x2;
// 		} 
// 		else 
// 			x = x2; y = y2; xe = x1;
// 		p_px(contr, x, y, color);
// 		for(i = 0; x < xe; i++) 
// 		{
// 			x = x + 1;		
// 			if (px < 0) 
// 				px = px + 2 * dy1;
// 			else
// 			{
// 				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) 
// 					y = y + 1;
// 				else 
// 					y = y - 1;
// 				px = px + 2 * (dy1 - dx1);
// 			}
// 			p_px(contr, x, y, color);
// 		}
				
// 	} 
// 	else 
// 	{ 
// 		if (dy >= 0) 
// 		{
// 			x = x1; 
// 			y = y1; 
// 			ye = y2;
// 		} 
// 		else 
// 			x = x2; y = y2; ye = y1;
// 		p_px(contr, x, y, color);	
// 		//pixel(x, y); // Draw first pixel
				
// 				// Rasterize the line
// 		for (i = 0; y < ye; i++) 
// 		{
// 			y = y + 1;
					
// 			// Deal with octants...
// 			if (py <= 0) 
// 			{
// 				py = py + 2 * dx1;
// 			} 
// 			else 
// 			{
// 				if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) 
// 				{
// 					x = x + 1;
// 				} 
// 				else 
// 				{
// 					x = x - 1;
// 				}
// 				py = py + 2 * (dx1 - dy1);
// 			}
					
// 						// Draw pixel from line span at
// 						// currently rasterized position
// 			p_px(contr, x, y, color);
// 				//	pixel(x, y);
// 		}
// 	}
// }
