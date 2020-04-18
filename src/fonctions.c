/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:43:19 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 15:38:32 by edal--ce         ###   ########.fr       */
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

void			free_mand(t_contr *contr)
{
	if (contr->map_parser.tx_n)
		mlx_destroy_image(contr->mlx, contr->textures[0].texture.img);
	if (contr->map_parser.tx_s)
		mlx_destroy_image(contr->mlx, contr->textures[1].texture.img);
	if (contr->map_parser.tx_w)
		mlx_destroy_image(contr->mlx, contr->textures[2].texture.img);
	if (contr->map_parser.tx_e)
		mlx_destroy_image(contr->mlx, contr->textures[3].texture.img);
	if (contr->map_parser.spr)
		mlx_destroy_image(contr->mlx, contr->textures[4].texture.img);
}

char			**get_up_map(char **oldmap, int size, t_contr *contr)
{
	char	**newmap;
	int		i;

	i = 0;
	if (!(newmap = malloc(sizeof(char*) * (size + 1))))
		close_(contr, "Error \nFAILED MALLOC");
	while (i < size && oldmap)
	{
		newmap[i] = oldmap[i];
		i++;
	}
	free(oldmap);
	return (newmap);
}
