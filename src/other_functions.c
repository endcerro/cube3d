/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 05:19:05 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/24 12:07:20 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int		v_color(t_color c)
{
	if (c.r < 0 || c.r > 255)
		return (0);
	if (c.b < 0 || c.b > 255)
		return (0);
	if (c.g < 0 || c.g > 255)
		return (0);
	return (1);
}

int		next_color(t_contr *ctr, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i++] != ',')
		close_(ctr, "Error\nCOLORS NOT VALID");
	return (i);
}

void	get_fc_colors(char *line, t_contr *contr)
{
	t_color		c;
	int			offset;

	c.r = -1;
	c.g = -1;
	c.b = -1;
	if (*line == 'F' || *line == 'C')
	{
		offset = 2;
		c.r = ft_atoi(line + offset);
		offset += next_color(contr, line + offset);
		c.g = ft_atoi(line + offset);
		offset += next_color(contr, line + offset);
		c.b = ft_atoi(line + offset);
	}
	if (!v_color(c))
		close_(contr, "Error\nREADING COLORS\n");
	if (*line == 'F' && (contr->map_parser.c_f += 1))
		contr->f_color = (c.r << 16) | (c.g << 8) | c.b;
	else if (*line == 'C' && (contr->map_parser.c_c += 1))
		contr->c_color = (c.r << 16) | (c.g << 8) | c.b;
	if (contr->map_parser.c_c > 1 || contr->map_parser.c_f > 1)
		close_(contr, "Error\nREADING COLORS\n");
}
