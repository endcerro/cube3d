/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loaders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:54:47 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/15 20:41:17 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/header.h"

// void	get_text_NO(char *line, t_contr *contr)//, int val)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 2;
// 	if (line[0] != 'N' || line[1] != 'O')
// 		close_(contr, "ERROR IN GETTING NORTH TEXTURE\n");
// 	while (ft_isspace(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line + i));
// 	//printf("NO TEXTURE PATH = %s\n", tmp);
// 	texture_loadr(tmp, contr);
// 	free(tmp);
// }

// void	get_text_SO(char *line, t_contr *contr)//, int val)
// {
// 	int i;
// 	char *tmp;

// 	i = 2;
// 	if (line[0] != 'S' || line[1] != 'O')
// 		close_(contr, "ERROR IN GETTING SOUTH TEXTURE\n");
// 	while (ft_isspace(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line + i));
// 	// printf("SO TEXTURE PATH = %s\n", tmp);
// 	texture_loadr(tmp, contr);
// 	free(tmp);
// }

// void	get_text_WE(char *line, t_contr *contr)//, int val)
// {
// 	int 	i;
// 	char 	*tmp;

// 	i = 2;
// 	if (line[0] != 'W' || line[1] != 'E')
// 		close_(contr, "ERROR IN GETTING WEST TEXTURE\n");
// 	while (ft_isspace(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line + i));
// 	// printf("WE TEXTURE PATH = %s\n", tmp);
// 	texture_loadr(tmp, contr);
// 	free(tmp);
// }

// void	get_text_EA(char *line, t_contr *contr)//, int val)
// {
// 	int 	i;
// 	char 	*tmp;

// 	i = 2;
// 	if (line[0] != 'E' || line[1] != 'A')
// 		close_(contr, "ERROR IN GETTING EAST TEXTURE\n");
// 	while (ft_isspace(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line + i));
// 	// printf("EA TEXTURE PATH = %s\n", tmp);
// 	texture_loadr(tmp, contr);
// 	free(tmp);
// }

// void	get_text_SPR(char *line, t_contr *contr)//, int val)
// {
// 	int 	i;
// 	char 	*tmp;
	
// 	i = 1;
// 	if(line[0] != 'S')
// 		close_(contr, "ERROR IN GETTING SPRITE TEXTURE\n");
// 	while(ft_isspace(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line + i));
// 	// printf("SPR TEXTURE PATH = %s\n", tmp);
// 	texture_loadr(tmp, contr);
// 	free(tmp);
// }