/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 05:19:05 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 04:53:00 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

#ifdef BONUS

void	free_mand(t_contr *contr)
{
	ft_putstr_fd("Your score is : ", 1);
	ft_putnbr_fd(contr->score, 1);
	ft_putstr_fd(" ! \n", 1);
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

#else

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

#endif

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
		close_(ctr, "Error\n COLORS NOT VALID");
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
		close_(contr, "Error \nREADING COLORS\n");
	if (*line == 'F')
		contr->f_color = (c.r << 16) | (c.g << 8) | c.b;
	else if (*line == 'C')
		contr->c_color = (c.r << 16) | (c.g << 8) | c.b;
}
