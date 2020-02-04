/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:41:01 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/04 06:23:15 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/header.h"
#include <fcntl.h>

void get_res(char *line, t_contr *contr)
{
	if(*line != 'R')
	{
		printf("ERROR IN GETTING RESOLUTION\n");
		exit(0);
	}
	int height = -1;
	int width = -1;
	int offset = 1;

	width = ft_atoi(line + offset++);
	while(ft_isdigit(line[offset]))
		offset++;
	height = ft_atoi(line + offset);
	if(width <= 0  || height <= 0)
	{
		printf("ERROR IN GETTING RESOLUTION\n");
		exit(0);
	}
	contr->res_h = width;
	contr->res_w = height;
	printf("RES LOAD: width %d heigt %d\n", width, height);
}

void get_text_NO(char *line, t_contr *contr, int val)
{
	if(line[0] != 'N' || line[1] != 'O')
	{
		printf("ERROR IN GETTING NORTH TEXTURE\n");
		exit(0);
	}
	int offset = 3;
	char *test = ft_substr(line, offset, ft_strlen(line + offset));
	printf("NO TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
}
void get_text_SO(char *line, t_contr *contr, int val)
{
	if(line[0] != 'S' || line[1] != 'O')
	{
		printf("ERROR IN GETTING SOUTH TEXTURE\n");
		exit(0);
	}
	int offset = 3;
	char *test = ft_substr(line, offset, ft_strlen(line + offset));
	printf("SO TEXTURE PATH = %s\n", test);
texture_loadr(test, contr);
}
void get_text_WE(char *line, t_contr *contr, int val)
{
	if(line[0] != 'W' || line[1] != 'E')
	{
		printf("ERROR IN GETTING WEST TEXTURE\n");
		exit(0);
	}
	int offset = 3;
	char *test = ft_substr(line, offset, ft_strlen(line + offset));
	printf("WE TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
}
void get_text_EA(char *line, t_contr *contr, int val)
{
	if(line[0] != 'E' || line[1] != 'A')
	{
		printf("ERROR IN GETTING EAST TEXTURE\n");
		exit(0);
	}
	int offset = 3;
	char *test = ft_substr(line, offset, ft_strlen(line + offset));
	printf("EA TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
}
void get_text_SPR(char *line, t_contr *contr, int val)
{
	if(line[0] != 'S')
	{
		printf("ERROR IN GETTING SPRITE TEXTURE\n");
		exit(0);
	}
	int offset = 2;
	char *test = ft_substr(line, offset, ft_strlen(line + offset));
	printf("SPR TEXTURE PATH = %s\n", test);
	texture_loadr(test, contr);
}

void get_fc_colors(char *line, t_contr *contr, int val)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int offset = 0;
	if(*line == 'F' || *line == 'C')
	{
		offset = 2;
		r = ft_atoi(line + offset);
		while(ft_isdigit(line[offset]))
		 	offset++;
		offset++;
		g = ft_atoi(line + offset);
		while(ft_isdigit(line[offset]))
			offset++;
		offset++;
		b = ft_atoi(line + offset);
	}
	printf("R = %d  G = %d B = %d \n",r,g,b );
	if(*line == 'F')
		contr->f_color = (r << 16) | ( g <<8) | b;
	else if(*line == 'C')
		contr->c_color = (r << 16) | ( g <<8) | b;
	 // ((r&0x0ff)<<16)|((g&0x0ff)<<8)|(b&0x0ff);

}


void load_map_B(t_contr *contr, int fd)
{
	char **map;
	int p = 0;
	int read = 1;
	map = malloc(sizeof(char*) * 100);
	while(read)
	{
		read = get_next_line(fd, &map[p++]);
		//parseline(line, contr, &val);
	}
	printf("NEW MAP\n");
	contr->map_w = ft_strlen(map[0]);
	contr->map_h = p;

	for(int i = 0; i < contr->map_h; i++)
	{
		for(int j = 0; j <contr->map_w; j++)
			printf("%c",map[i][j]);
		printf("\n");
	}
	contr->map = map;
	printf("OUT\n");


	//map = malloc()
}

void parseline(char *line, t_contr *contr, int *val)
{
	//printf("FIST CHAR %d\n",*line );
	if(*line == '\n' || *line == 0)
		*val = *val - 1;
	else if(*val == 0)
		get_res(line, contr);
	else if(*val == 1)
		get_text_NO(line, contr, *val);
	else if(*val == 2)
		get_text_SO(line, contr, *val);
	else if(*val == 3)
		get_text_WE(line, contr, *val);
	else if(*val == 4)
		get_text_EA(line, contr, *val);
	else if(*val == 5)
		get_text_SPR(line, contr, *val);
	else if(*val == 6)
		get_fc_colors(line, contr, *val);
	else if(*val == 7)
		get_fc_colors(line, contr, *val);
	// else if(val > 7)
	// 	get_map()
	*val = *val + 1;
	free(line);
}

void load_cub(char *filename, t_contr* contr)
{
	char *line;
	int fd;

	fd = open(filename, O_RDONLY);
	int done = 0;

	int read = 1;
	int val = 0;
	while(read && val < 8)
	{
		read = get_next_line(fd, &line);
		parseline(line, contr, &val);
	}
	load_map_B(contr, fd);

}