/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loaders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:54:47 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/15 20:54:21 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/header.h"

void get_text_NO(char *line, t_contr *contr)//, int val)
{
	if(line[0] != 'N' || line[1] != 'O')
	{
		close_(contr, "ERROR IN GETTING NORTH TEXTURE\n");
		//printf("ERROR IN GETTING NORTH TEXTURE\n");
		//exit(0);
	}
	int i = 2;
	while(ft_isspace(line[i]))
		i++;
	char *test = ft_substr(line, i, ft_strlen(line + i));
	printf("NO TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
	free(test);
}
void get_text_SO(char *line, t_contr *contr)//, int val)
{
	if(line[0] != 'S' || line[1] != 'O')
		close_(contr, "ERROR IN GETTING SOUTH TEXTURE\n");
	int i = 2;
	while(ft_isspace(line[i]))
		i++;
	char *test = ft_substr(line, i, ft_strlen(line + i));
	printf("SO TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
	free(test);
}
void get_text_WE(char *line, t_contr *contr)//, int val)
{
	if(line[0] != 'W' || line[1] != 'E')
		close_(contr, "ERROR IN GETTING WEST TEXTURE\n");
	int i = 2;
	while(ft_isspace(line[i]))
		i++;
	char *test = ft_substr(line, i, ft_strlen(line + i));
	printf("WE TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
	free(test);
}
void get_text_EA(char *line, t_contr *contr)//, int val)
{
	if(line[0] != 'E' || line[1] != 'A')
		close_(contr, "ERROR IN GETTING EAST TEXTURE\n");
	int i = 2;
	while(ft_isspace(line[i]))
		i++;
	char *test = ft_substr(line, i, ft_strlen(line + i));
	printf("EA TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
	free(test);
}
void get_text_SPR(char *line, t_contr *contr)//, int val)
{
	if(line[0] != 'S')
		close_(contr, "ERROR IN GETTING SPRITE TEXTURE\n");
	int i = 1;
	while(ft_isspace(line[i]))
		i++;
	char *test = ft_substr(line, i, ft_strlen(line + i));
	printf("SPR TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
	free(test);
}