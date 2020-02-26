/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 05:19:05 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 05:36:26 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	free_mand(t_contr *contr)
{
	if (contr->basic_sprites[0] == 1)
		mlx_destroy_image(contr->mlx, contr->textures[0].texture.img);
	if (contr->basic_sprites[1] == 1)
		mlx_destroy_image(contr->mlx, contr->textures[1].texture.img);
	if (contr->basic_sprites[2] == 1)
		mlx_destroy_image(contr->mlx, contr->textures[2].texture.img);
	if (contr->basic_sprites[3] == 1)
		mlx_destroy_image(contr->mlx, contr->textures[3].texture.img);
	if (contr->basic_sprites[4] == 1)
		mlx_destroy_image(contr->mlx, contr->textures[4].texture.img);
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
		while (ft_isdigit(line[offset]))
			offset++;
		offset++;
		c.g = ft_atoi(line + offset);
		while (ft_isdigit(line[offset]))
			offset++;
		offset++;
		c.b = ft_atoi(line + offset);
	}
	if (c.b == -1 || c.r == -1 || c.g == -1)
		close_(contr, "Error \nREADING COLORS\n");
	if (*line == 'F')
		contr->f_color = (c.r << 16) | (c.g << 8) | c.b;
	else if (*line == 'C')
		contr->c_color = (c.r << 16) | (c.g << 8) | c.b;
}

void	menu_mode(t_contr *contr)
{
	if (contr->res.y < 400 || contr->res.x < 400)
	{
		write(1, "MENU NOT AVAILABLE AT THIS RESOLUTION", 33);
		contr->menu_mode = 0;
		return ;
	}
	print_menu(contr, 0, 0);
}