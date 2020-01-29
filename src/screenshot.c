/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:04:39 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/29 16:50:00 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

	//
	typedef struct __attribute__((__packed__)) s_bmp_fhead 
	{
		unsigned char 	type[2];
		int 			file_size;
		short			reserved1;
		short			reserved2;
		unsigned int	offset;
	}	t_bmp_fhead;
	typedef struct __attribute__((__packed__)) s_bmp_ihead {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
	} t_bmp_ihead;
int get_screenshot(t_contr *contr)
{
	int fd;
	fd = open("screenshot.bmp", O_APPEND | O_TRUNC | O_WRONLY | O_CREAT, 0644);

	int image_size = contr->res_h * contr->res_w;
	struct s_bmp_fhead head; 
	struct s_bmp_ihead im_head;
	
	ft_memcpy(&head.type, "BM", 2);	
	head.file_size       = image_size + 54;;
	head.reserved1       = 0;
	head.reserved2       = 0;
	head.offset 		 = 54;

	im_head.size_header     = 40;
	im_head.width           = contr->res_w;
	im_head.height          = contr->res_h; 
	im_head.planes          = 1;
	im_head.bit_count       = 32;
	im_head.compression     = 0;
	im_head.image_size      = image_size;
	im_head.ppm_x           = 1; //BLK
	im_head.ppm_y           = 1;//BLK
	im_head.clr_used        = 0;
	im_head.clr_important   = 0;
		
	write(fd, &head, 14);
	write(fd, &im_head, sizeof(t_bmp_ihead));
	
	
	int color;
	t_text text;
	for(int i = 0; i < contr->res_h; i++)
	{
		for (int j = 0; j < contr->res_w; j++)
		{
			text.texture = contr->img;
			color = g_px(text,j, contr->res_h - i);
			//R = 0xff0000 & color;
			//G = 0xff00 & color;
			//B = 0xff & color;
			write(fd, &color, sizeof(int));
		}	
	}

//	printf("Here");
// write(fd, sizeof(color), image);
//}
	close(fd);
	return 0;
}
