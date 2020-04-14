/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loaders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:54:47 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/14 15:04:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	get_text_no(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'N' || line[1] != 'O')
		close_(contr, "Error\n GETTING NORTH TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	texture_loadr(tmp, contr, 0);
	free(tmp);
}

void	get_text_so(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'S' || line[1] != 'O')
		close_(contr, "Error\n GETTING SOUTH TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	texture_loadr(tmp, contr, 1);
	free(tmp);
}

void	get_text_we(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'W' || line[1] != 'E')
		close_(contr, "Error\n GETTING WEST TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	texture_loadr(tmp, contr, 2);
	free(tmp);
}

void	get_text_ea(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'E' || line[1] != 'A')
		close_(contr, "Error\n GETTING EAST TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	texture_loadr(tmp, contr, 3);
	free(tmp);
}

void	get_text_spr(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 1;
	if (line[0] != 'S')
		close_(contr, "Error\n GETTING SPRITE TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	texture_loadr(tmp, contr, 4);
	free(tmp);
}
