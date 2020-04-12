/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:17:06 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/12 15:22:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	free_after(t_contr *contr, int i)
{
	int j;

	j = 0;
	while (i + j < contr->mpd.y)
		free(contr->map[i + j++]);
	contr->mpd.y -= j;
}

void	sub_load(t_contr *contr, int i)
{
	int j;

	j = -1;
	while (++j < contr->mpd.x)
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

char** grow_map(t_contr *contr)
{
	unsigned int biggest;
	int i;
	char **tmp;
	char **cp;

	tmp = malloc(sizeof(char*) * 100);
	cp = tmp;
	i = -1;
	biggest = 0;
	while (++i < contr->mpd.y)
	{
		if(ft_strlen(contr->map[i]) > biggest)
			biggest = ft_strlen(contr->map[i]);
	}
	i = -1;
	while (++i < contr->mpd.y)
	{
		if(ft_strlen(contr->map[i]) < biggest)
			*(tmp++) = ft_strjoin_fill(contr->map[i],'0', biggest - ft_strlen(contr->map[i]));
		else
			*(tmp++)= ft_strdup(contr->map[i]);
	}
	*tmp = 0;
	return cp;
}

void free_tmp(char **tmp, int d)
{
	int i;

	i = -1;
	while (++i < d)
		free(tmp[i]);
	free(tmp);
}
void flood_fill (t_contr *contr, int i, int j, char **map)
{
	if(i < 0 || j < 0 || map[i] == 0)
		return;
	else if(map[i][j] == 'C')
		return;
	else if(map[i][j] == '1' || map[i][j] == 0)
		return;
	else if (map[i][j] != 0)
		map[i][j] = 'C';
	flood_fill(contr, i + 1,j, map);
	flood_fill(contr, i - 1,j, map);
	flood_fill(contr, i,j + 1, map);
	flood_fill(contr, i,j - 1, map);

}
int check_if_closed(t_contr *contr, char **map)
{
	int i;

	i = 0;
	if (ft_pos_c_str(map[i++], 'C') > 0)
		return (0);
	while (i < contr->mpd.x && map[i])
	{
		if (map[i][0] == 'C' || map[i][ft_strlen(map[i])] == 'C')
			return (0);
		i++;
	}
	if (ft_pos_c_str(map[i - 1], 'C') > 0)
		return (0);
	return 1;
}

void printmap(t_contr *contr, char **map)
{
	int i;

	i = 0;
	printf("--------------------\n");
	while (i < contr->mpd.x && map[i])
	{
		printf("%s\n",map[i++]);
	}
	printf("--------------------\n");
	printf("\n\n");
}

int		parse_map(t_contr *contr)
{
	char **tmp;

	printmap(contr, contr->map);
	tmp = grow_map(contr);
	printmap(contr, tmp);
	flood_fill(contr, (int)contr->pos.y, (int)contr->pos.x, tmp);
	if(check_if_closed(contr, tmp) == 0)
	{
		printmap(contr,tmp);
		close_(contr, "NOT CLOSED\n");
	}
	printmap(contr,tmp);
	free_tmp(tmp, contr->mpd.y);
	return (1);
}





void	parse_sprites(t_contr *contr)
{
	int			i;
	int			j;
	int			*sprite_nb;
	t_sprite	*sprites;

	i = -1;
	j = 0;
	sprites = (contr->sprites);
	sprite_nb = &(contr->sprites_nb);
	while (++i < contr->mpd.y)
	{
		j = -1;
		while (++j < contr->mpd.x)
		{
			if (contr->map[i][j] == '2' || contr->map[i][j] == '3')
			{
				sprites[*sprite_nb].y = i + 0.5;
				sprites[*sprite_nb].x = j + 0.5;
				sprites[*sprite_nb].texture = contr->textures[4];
				if (contr->map[i][j] == '3' && (contr->map[i][j] = '0'))
					contr->enn_id = *sprite_nb;
				(*sprite_nb)++;
			}
		}
	}
}
