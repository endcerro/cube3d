/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:17:06 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 04:58:46 by edal--ce         ###   ########.fr       */
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
	// printf("SET at %f %f \n",contr->pos.x,contr->pos.y);
}

char** grow_map(t_contr *contr)
{
	int biggest;
	int i;
	char **tmp;
	char **cp;

	tmp = malloc(sizeof(char*) * 100);
	cp = tmp;
	i = -1;
	biggest = 0;
	while (++i < contr->mpd.y)
	{
		// printf("len = %d\n",ft_strlen(contr->map[i]) );
		if(ft_strlen(contr->map[i]) > biggest)
		{
			// printf("HERE\n");
			biggest = ft_strlen(contr->map[i]);
		}
	}
	i = -1;
	// printf("biggest = %d\n",biggest );
	while (++i < contr->mpd.y)
	{
		if(ft_strlen(contr->map[i]) < biggest)
		{
			// printf("before %s\n",contr->map[i]);
			*(tmp++)= ft_strjoin_fill(contr->map[i],'0', biggest - ft_strlen(contr->map[i]));
			// printf("after %s\n",*(tmp - 1));
		}
		else
		{
			*(tmp++)= ft_strdup(contr->map[i]);
		}
	}
	*tmp = 0;
	return cp;
}

int		parse_map(t_contr *contr)
{
	int i;
	char **tmp;

	i = -1;
	printmap(contr, contr->map);

	// printf("Loading at %f %f\n", contr->pos.y,contr->pos.x);
	// flood_fill(contr, 1,1);
	tmp = grow_map(contr);
	printmap(contr, tmp);

	// while (++i < contr->mpd.x)
	// {
	// 	if (contr->map[0][i] != '1' || contr->map[contr->mpd.y - 1][i] != '1')
	// 		close_(contr, "Error\nMAP NOT CLOSED 1\n");
	// }
	// i = -1;
	// while (++i < contr->mpd.y)
	// {
	// 	if (contr->map[i][0] != '1' || contr->map[i][contr->mpd.x - 1] != '1')
	// 		close_(contr, "Error\nMAP NOT CLOSED 2\n");
	// }
	// for(int k = 0; k < contr->mpd.y; k++)
	// {
	// 	// printf("%s\n",contr->map[k]);
	// }
	flood_fill(contr, (int)contr->pos.y, (int)contr->pos.x, tmp);
	if(check_if_closed(contr, tmp) == 0)
	{
		printmap(contr,tmp);
		write(1,"NOT CLOSED\n",11);
		exit(0);
	}
	printmap(contr,tmp);

	return (1);
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

int check_if_closed(t_contr *contr, char **map)
{
	t_vpi gap;
	int i;
	int j;

	j = 0;
	i = 0;
	// printf("TOP OPEN %d\n",ft_pos_c_str(contr->map[0], 'C'));
	if(ft_pos_c_str(map[0], 'C') > 0)
	{
		return 0;
	}
	// if(ft_pos_c_str(contr->map[contr->mpd.x - 2], 'C') > 0)
	// {
	// 	printf("BOT OPEN\n");
	// }
	i = 0;
	while (i < contr->mpd.x && map[i])
	{
		if(map[i][0] == 'C' || map[i][ft_strlen(map[i])] == 'C')
			return 0;
		i++;
	}
	if(ft_pos_c_str(map[i - 1], 'C') > 0)
	{
		return 0;
	}
	return 1;
}

void flood_fill (t_contr *contr, int i, int j, char **map)
{
	// write(1,"in i =",6);
	// ft_putnbr_fd(i,1);
	// write(1," j =",4);
	// ft_putnbr_fd(j,1);
	// write(1,"\n",1);
	if(i < 0 || j < 0)
		return;
	if(map[i] == 0)
	{
		// ft_putstr_fd("return ,end of grid\n", 1);
		return;
	}
	if(map[i][j] == 'C')
	{
		// ft_putstr_fd("return ,C here\n", 1);
		return;
	}
	if(map[i][j] == '1' || map[i][j] == 0)
	{
		// ft_putstr_fd("1 here\n", 1);
		return;
	}
	else if (map[i][j] != 0)
	{

		// ft_putstr_fd("adding C\n", 1);
		map[i][j] = 'C';
		// printf("af %c\n", );
	}
	flood_fill(contr, i + 1,j, map);
	flood_fill(contr, i - 1,j, map);
	flood_fill(contr, i,j + 1, map);
	flood_fill(contr, i,j - 1, map);
			// write(1,"out",3);

	
 // 1. If target-color is equal to replacement-color, return.
 // 2. ElseIf the color of node is not equal to target-color, return.
 // 3. Else Set the color of node to replacement-color.
 // 4. Perform Flood-fill (one step to the south of node, target-color, replacement-color).
 //    Perform Flood-fill (one step to the north of node, target-color, replacement-color).
 //    Perform Flood-fill (one step to the west of node, target-color, replacement-color).
 //    Perform Flood-fill (one step to the east of node, target-color, replacement-color).
 // 5. Return.
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
