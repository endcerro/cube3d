/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:04:39 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 13:14:34 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../header/header.h"

void	sort_sprites(double *sprite_dist, int *sprite_ord, int cpt)
{
	int i;
	int tmp;

	i = 0;
	while (i < cpt - 1)
	{
		if (sprite_dist[sprite_ord[i]] < sprite_dist[sprite_ord[i + 1]])
		{
			tmp = sprite_ord[i];
			sprite_ord[i] = sprite_ord[i + 1];
			sprite_ord[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

int		write_header(t_contr *contr, int fd)
{
	int			i;
	t_bmp_fhead head;
	t_bmp_ihead im_head;

	ft_memcpy(&head.type, "BM", 2);
	head.file_size = contr->res.y * contr->res.x + 54;
	head.reserved1 = 0;
	head.reserved2 = 0;
	head.offset = 54;
	im_head.size_header = 40;
	im_head.width = contr->res.x;
	im_head.height = contr->res.y;
	im_head.planes = 1;
	im_head.bit_count = 32;
	im_head.compression = 0;
	im_head.image_size = contr->res.y * contr->res.x;
	im_head.ppm_x = 1;
	im_head.ppm_y = 1;
	im_head.clr_used = 0;
	im_head.clr_important = 0;
	i = write(fd, &head, 14);
	i = write(fd, &im_head, sizeof(t_bmp_ihead));
	return (i);
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
	while (++i < contr->res.y)
	{
		j = -1;
		while (++j < contr->res.x)
		{
			text.texture = contr->img;
			color = g_px(text, j, contr->res.y - i);
			color = write(fd, &color, sizeof(int));
		}
	}
	close(fd);
}
