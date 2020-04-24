/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:17:06 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 18:14:38 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

char	**grow_map(t_contr *contr)
{
	unsigned int	biggest;
	int				i;
	char			**tmp;
	char			**cp;

	if (!(tmp = malloc(sizeof(char*) * 100)))
		return (0);
	cp = tmp;
	i = -1;
	biggest = 0;
	while (++i < contr->mpd.y)
	{
		if (ft_strlen(contr->map[i]) > biggest)
			biggest = ft_strlen(contr->map[i]);
	}
	i = -1;
	while (++i < contr->mpd.y)
		if (ft_strlen(contr->map[i]) < biggest)
			*(tmp++) = ft_strjoin_fill(contr->map[i], '0', biggest -
				ft_strlen(contr->map[i]));
		else
			*(tmp++) = ft_strdup(contr->map[i]);
	*tmp = '\0';
	contr->mpd.x = biggest;
	return (cp);
}

void	free_tmp(char **tmp, int d)
{
	int i;

	i = -1;
	while (++i < d)
		free(tmp[i]);
	free(tmp);
}

void	flood_fill(t_contr *contr, int i, int j, char **map)
{
	if (i < 0 || j < 0 || map[i] == 0)
		return ;
	else if (map[i][j] == 'C')
		return ;
	else if (map[i][j] == '1' || map[i][j] == 0)
		return ;
	else if (map[i][j] != 0)
		map[i][j] = 'C';
	flood_fill(contr, i + 1, j, map);
	flood_fill(contr, i - 1, j, map);
	flood_fill(contr, i, j + 1, map);
	flood_fill(contr, i, j - 1, map);
}

int		check_if_closed(t_contr *contr, char **map)
{
	int i;

	i = 0;
	if (ft_pos_c_str(map[i++], 'C') > 0)
		return (0);
	while (i < contr->mpd.y && map[i])
	{
		if (map[i][0] == 'C' || map[i][ft_strlen(map[i]) - 1] == 'C')
			return (0);
		i++;
	}
	if (ft_pos_c_str(map[i - 1], 'C') > 0)
		return (0);
	return (1);
}
