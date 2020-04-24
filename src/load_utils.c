/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:17:06 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/24 12:07:22 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	sub_load(t_contr *contr, int i)
{
	unsigned int j;

	j = 0;
	while (++j < ft_strlen(contr->map[i]))
	{
		if (contr->map[i][j] == 'N' && contr->pos.x == -1)
			set_n(contr, i, j);
		else if (contr->map[i][j] == 'S' && contr->pos.x == -1)
			set_s(contr, i, j);
		else if (contr->map[i][j] == 'E' && contr->pos.x == -1)
			set_e(contr, i, j);
		else if (contr->map[i][j] == 'W' && contr->pos.x == -1)
			set_w(contr, i, j);
	}
}

int		parse_map(t_contr *contr)
{
	char **tmp;

	tmp = grow_map(contr);
	flood_fill(contr, (int)contr->pos.y, (int)contr->pos.x, tmp);
	if (check_if_closed(contr, tmp) == 0)
	{
		free_tmp(tmp, contr->mpd.y);
		close_(contr, "Error\nMAP NOT CLOSED\n");
	}
	free_tmp(tmp, contr->mpd.y);
	return (1);
}

void	check_enn(t_contr *contr, int i, int j)
{
	if (contr->map[i][j] != '3')
		return ;
	contr->sprites_nb = contr->sprites_nb - 1;
	if (contr->bonus == 1)
	{
		contr->map[i][j] = '0';
		contr->enn_id = contr->sprites_nb++;
	}
}

void	parse_sprites(t_contr *contr)
{
	int			i;
	int			j;
	int			*sprite_nb;
	t_sprite	*sprites;

	i = -1;
	sprites = (contr->sprites);
	sprite_nb = &(contr->sprites_nb);
	while (++i < contr->mpd.y)
	{
		j = -1;
		while (contr->map[i][++j])
		{
			if (contr->map[i][j] == '2' || contr->map[i][j] == '3')
			{
				sprites[*sprite_nb].y = i + 0.5;
				sprites[*sprite_nb].x = j + 0.5;
				sprites[*sprite_nb].texture = contr->textures[4];
				(*sprite_nb)++;
				check_enn(contr, i, j);
			}
		}
	}
}

void	get_res(char *line, t_contr *contr)
{
	int		height;
	int		width;
	int		offset;
	int		x;
	int		y;

	offset = 1;
	width = ft_atoi(line + offset++);
	while (ft_isspace(line[offset]))
		offset++;
	while (ft_isdigit(line[offset]))
		offset++;
	height = ft_atoi(line + offset);
	if (width <= 0 || height <= 0 || contr->map_parser.res == 1)
		close_(contr, "Error\nGETTING RESOLUTION");
	mlx_get_screen_size(contr->mlx, &x, &y);
	contr->res.x = (width > x) ? x : width;
	contr->res.y = (height > y) ? y : height;
	contr->map_parser.res = 1;
}
