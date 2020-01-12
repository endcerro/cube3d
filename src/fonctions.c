#include "../header/header.h"



void print_image(t_contr *contr, int x, int y)
{

	//printf("RENDERED");
	mlx_clear_window(contr->mlx_ptr, contr->win_ptr);
	mlx_put_image_to_window(contr->mlx_ptr, contr->win_ptr, (contr->img).img, x, y);
   	mlx_destroy_image(contr->mlx_ptr, contr->img.img);

   	contr->img.img = mlx_new_image(contr->mlx_ptr, contr->res_w, contr->res_h);
	contr->img.addr =  mlx_get_data_addr(contr->img.img, &(contr->img.bpp), &(contr->img.length), &(contr->img.endian));

}


void            my_mlx_pixel_put(t_contr *contr, int x, int y, int color)
{
    char    *dst;
    t_img img;
    img = contr->img;
    dst = img.addr + (y * img.length + x * (img.bpp / 8));
    *(unsigned int*)dst = (unsigned int)color;
}

void draw_line(double x1, double y1, double x2, double y2, t_contr *contr, int color)
{
	
	double x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	dx1 = ft_abs_double(dx);
	dy1 = ft_abs_double(dy);
	
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; 
			y = y1; 
			xe = x2;
		} 
		else 
		{ // Line is drawn right to left (swap ends)
			x = x2; y = y2; xe = x1;
		}
		my_mlx_pixel_put(contr, x, y, color);
				//pixel(x, y); // Draw first pixel
				
				// Rasterize the line
		for(i = 0; x < xe; i++) 
		{
			x = x + 1;		
						// Deal with octants...
			if (px < 0) 
			{
				px = px + 2 * dy1;
			} 
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) 
				{
					y = y + 1;
				} 
				else 
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
					
						// Draw pixel from line span at
						// currently rasterized position
			my_mlx_pixel_put(contr, x, y, color);
		}
				
	} 
	else 
	{ // The line is Y-axis dominant
			
				// Line is drawn bottom to top
		if (dy >= 0) 
		{
			x = x1; 
			y = y1; 
			ye = y2;
		} 
		else 
		{ // Line is drawn top to bottom
			x = x2; y = y2; ye = y1;
		}
		my_mlx_pixel_put(contr, x, y, color);	
		//pixel(x, y); // Draw first pixel
				
				// Rasterize the line
		for (i = 0; y < ye; i++) 
		{
			y = y + 1;
					
			// Deal with octants...
			if (py <= 0) 
			{
				py = py + 2 * dx1;
			} 
			else 
			{
				if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) 
				{
					x = x + 1;
				} 
				else 
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
					
						// Draw pixel from line span at
						// currently rasterized position
			my_mlx_pixel_put(contr, x, y, color);
				//	pixel(x, y);
		}
	}
}