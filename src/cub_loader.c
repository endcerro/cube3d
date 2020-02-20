/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:41:01 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/20 13:03:32 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/header.h"
#include <fcntl.h>



int parse_map(t_contr *contr)
{
	int i;

	i = -1;
	printf("MAP H = %d MAP W = %d \n", contr->map_h, contr->map_w);
	while(++i < contr->map_w)
	{
		if(contr->map[0][i] != '1' || contr->map[contr->map_h - 1][i] != '1' ) //|| contr->map[contr->map_w - 1][i] != '1' )
			printf("MAP NOT CLOSED\n");
		// i++;
	}
	i = -1;
	while(++i < contr->map_h)
	{
		if(contr->map[i][0] != '1' || contr->map[i][contr->map_w - 1] != '1' ) //|| contr->map[contr->map_w - 1][i] != '1' )
			printf("MAP NOT CLOSED\n");
		// i++;
	}
	return 1;
}

void parse_sprites(t_contr *contr)
{
	int i = 0;
	int j = 0;
	t_sprite *sprites = (contr->sprites);
	int *sprite_nb = &(contr->sprites_nb);
	*sprite_nb = 0;
	while(i < contr->map_h)
	{
		j = 0;
		while(j < contr->map_w)
		{
			if(contr->map[i][j] == '2')// || contr->map[i][contr->map_w - 1] != '1' ) //|| contr->map[contr->map_w - 1][i] != '1' )
			{
				sprites[*sprite_nb].y = i + 0.5;
				sprites[*sprite_nb].x = j + 0.5;
				sprites[*sprite_nb].texture = contr->textures[4];
				(*sprite_nb)++;
			}
			j++;
		}
		i++;
	}
}

void get_res(char *line, t_contr *contr)
{
	int height;
	int width;
	int offset;
	offset = 1;
	height = ft_atoi(line + offset++);
	while(ft_isdigit(line[offset]))
		offset++;
	width = ft_atoi(line + offset);
	if(width <= 0  || height <= 0)
		close_(contr,"ERROR IN GETTING RESOLUTION");
	contr->res_h = (width > 2560) ? 2560 : width;
	contr->res_w = (height > 1440) ? 1440 : height;
	printf("RES LOAD: width %d heigt %d\n", contr->res_w, contr->res_h);
}



void get_fc_colors(char *line, t_contr *contr)//, int val)
{
	int r = -1;
	int g = -1;
	int b = -1;
	int offset;
	if(*line == 'F' || *line == 'C')
	{
		offset = 2;
		r = ft_atoi(line + offset);
		while(ft_isdigit(line[offset]))
		 	offset++;

		offset++;
//		if(!ft_isdigit(line[offset]))
//			printf("ERROR READING COLORS\n");
		g = ft_atoi(line + offset);
		while(ft_isdigit(line[offset]))
			offset++;
		offset++;
		b = ft_atoi(line + offset);
	}
	if(b == -1 || r == -1 || g == -1)
	{
		printf("ERROR READING COLORS\n");
		exit(0);
	}
	printf("R = %d  G = %d B = %d \n",r,g,b );
	if(*line == 'F')
		contr->f_color = (r << 16) | ( g <<8) | b;
	else if(*line == 'C')
		contr->c_color = (r << 16) | ( g <<8) | b;
	 // ((r&0x0ff)<<16)|((g&0x0ff)<<8)|(b&0x0ff);

}

double	get_fov(t_contr *contr)
{
	return(0.50 / (1.0 * contr->res_h / (1.0*contr->res_w)));
}

void load_map_B(t_contr *contr, int fd)
{
	char **map;
	int p = 0;
	int read = 1;
	if(!(map = malloc(sizeof(char*) * 100)))
		close_(contr, "FAILED MALLOC");
	while(read)
	{
		read = get_next_line(fd, &map[p++]);
		//parseline(line, contr, &val);
	}
	t_vp pos;
	pos.x = -1;
	pos.y = -1;
	contr->map_w = ft_strlen(map[0]);
	contr->map_h = p;

	contr->map = map;
	for(int i = 0; i < contr->map_h; i++)
	{
		if((int)ft_strlen(map[i]) != contr->map_w)
			close_(contr,"ERROR PARSING" );
		for(int j = 0; j <contr->map_w; j++)
		{
			if(map[i][j] == 'N' && pos.x == -1)
			{
				//printf("N");
				contr->pos.x = j + 0.5;
				contr->pos.y = i + 0.5;
				contr->dir.x = 0;
				contr->dir.y = -1;
				contr->plane.x = 0.66;
				contr->plane.x = get_fov(contr); 
				contr->plane.y = 0;
				map[i][j] = '0';
			}
			else if(map[i][j] == 'S' && pos.x == -1)
			{
				//printf("S");
				contr->pos.x = j + 0.5;
				contr->pos.y = i + 0.5;
				contr->dir.x = 0;
				contr->dir.y = 1;
				contr->plane.x = -0.66;
				contr->plane.x = -get_fov(contr); 
				contr->plane.y = 0;
				map[i][j] = '0';
				map[i][j] = '0';
			}
			else if(map[i][j] == 'E' && pos.x == -1)
			{
				contr->pos.x = j + 0.5;
				contr->pos.y = i + 0.5;
				contr->dir.x = 1;
				contr->dir.y = 0;
				contr->plane.x = 0;
				contr->plane.y = 0.66;
				contr->plane.y = get_fov(contr);

				map[i][j] = '0';
			}
			else if(map[i][j] == 'W' && pos.x == -1)
			{
				contr->pos.x = j + 0.5;
				contr->pos.y = i + 0.5;
				contr->dir.x = -1;
				contr->dir.y = 0;
				contr->plane.x = 0;
				contr->plane.y = -0.66;
				contr->plane.y = -get_fov(contr);
				map[i][j] = '0';
			}
			
			printf("%c",map[i][j]);
			
		}
		// if()
	//	int i = -1;
		printf("\n");
	}
	if(contr->pos.x == -1 || contr->pos.y == -1)
		close_(contr,"NO POS IN MAP ERROR\n");
	parse_map(contr);
	parse_sprites(contr);

	printf("OUT\n");


	//map = malloc()
}

void init_vals(t_contr *contr)
{
	contr->res_w = -1;
	contr->res_h = -1;
	// contr->
	//t_contr->res_w = -1;
}

int check_vals(t_contr *contr)
{
	if(contr->res_w == -1 || contr->res_h == -1)
		printf("ERROR PARSING MISSING VALUES\n");
	if(contr->text_nb != 5)
		printf("ERROR PARSING MISSING VALUES\n");
	return 1;
}

void parseline(char *line, t_contr *contr, int *val)
{
	printf("FIST CHAR %c, second = %c\n",line[0],line[1] );
	if(*line == '\n' || *line == 0)
		*val = *val - 1;
	else if(*line == 'R')
		get_res(line, contr);
	else if(*line == 'N' && line[1] == 'O' )
		get_text_no(line, contr);//, *val);
	else if(*line == 'S' && line[1] == 'O' )
		get_text_so(line, contr);//, *val);
	else if(*line == 'W' && line[1] == 'E' )
		get_text_we(line, contr);//, *val);
	else if(*line == 'E' && line[1] == 'A' )
		get_text_ea(line, contr);//, *val);
	else if(*line == 'S')
		get_text_spr(line, contr);//, *val);
	else if(*line == 'F')
		get_fc_colors(line, contr);//, *val);
	else if(*line == 'C')
		get_fc_colors(line, contr);//, *val);
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
	//int done = 0;

	int read = 1;
	int val = 0;
	while(read && val < 8)
	{
		read = get_next_line(fd, &line);
		parseline(line, contr, &val);
	}
	load_map_B(contr, fd);
	check_vals(contr);
}