/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:04:39 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/15 18:58:34 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	write_header(t_contr *contr, int fd)
{
	t_bmp_fhead head;
	t_bmp_ihead im_head;

	ft_memcpy(&head.type, "BM", 2);
	head.file_size = contr->res_h * contr->res_w + 54;
	head.reserved1 = 0;
	head.reserved2 = 0;
	head.offset = 54;
	im_head.size_header = 40;
	im_head.width = contr->res_w;
	im_head.height = contr->res_h;
	im_head.planes = 1;
	im_head.bit_count = 32;
	im_head.compression = 0;
	im_head.image_size = contr->res_h * contr->res_w;
	im_head.ppm_x = 1;
	im_head.ppm_y = 1;
	im_head.clr_used = 0;
	im_head.clr_important = 0;
	write(fd, &head, 14);
	write(fd, &im_head, sizeof(t_bmp_ihead));
}

void	get_screenshot(t_contr *contr)
{
	int		fd;
	int		color;
	int		i;
	int		j;
	t_text	text;

	i = -1;
	fd = open("screenshot.bmp", O_APPEND | O_TRUNC | O_WRONLY | O_CREAT, 0644);
	write_header(contr, fd);
	while (++i < contr->res_h)
	{
		j = -1;
		while (++j < contr->res_w)
		{
			text.texture = contr->img;
			color = g_px(text, j, contr->res_h - i);
			write(fd, &color, sizeof(int));
		}
	}
	close(fd);
}
