/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loaders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:54:47 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/20 13:05:48 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	get_text_no(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'N' || line[1] != 'O')
		close_(contr, "ERROR IN GETTING NORTH TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	printf("NO TEXTURE PATH = %s\n", tmp);
	texture_loadr(tmp, contr, 0);
	free(tmp);
}

void	get_text_so(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'S' || line[1] != 'O')
		close_(contr, "ERROR IN GETTING SOUTH TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	printf("SO TEXTURE PATH = %s\n", tmp);
	texture_loadr(tmp, contr, 1);
	free(tmp);
}

void	get_text_we(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'W' || line[1] != 'E')
		close_(contr, "ERROR IN GETTING WEST TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	printf("WE TEXTURE PATH = %s\n", tmp);
	texture_loadr(tmp, contr, 2);
	free(tmp);
}

void	get_text_ea(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 2;
	if (line[0] != 'E' || line[1] != 'A')
		close_(contr, "ERROR IN GETTING EAST TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	printf("EA TEXTURE PATH = %s\n", tmp);
	texture_loadr(tmp, contr, 3);
	free(tmp);
}

void	get_text_spr(char *line, t_contr *contr)
{
	int		i;
	char	*tmp;

	i = 1;
	if (line[0] != 'S')
		close_(contr, "ERROR IN GETTING SPRITE TEXTURE\n");
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line + i));
	printf("SPR TEXTURE PATH = %s\n", tmp);
	texture_loadr(tmp, contr, 4);
	free(tmp);
}
