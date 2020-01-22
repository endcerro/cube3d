/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 07:36:04 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 10:48:55 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"
#include <fcntl.h>

int ft_isspace(char *in)
{
	if (*in == ' ' || *in == '	' || *in == '\n'|| *in == '\t' || *in == '\v' || *in == '\f' || *in == '\r')
		return(1);
	return(0);
}

void get_res(char *line, t_contr *contr)
{
	int i;
	int w;
	int h;
	
	i = 1;
	while(ft_isspace(line + i))
		i++;
	w = ft_atoi(line + i);
	while(ft_isdigit(line[i]))
		i++;
	h = ft_atoi(line + i);
	if(h <= 0 || w <= 0)
	{
		printf("ERROR PARSING\n");
		exit(0);
	}
	printf("PARSED RES = %d %d \n",w,h );
}
void load_cub(char *filename, t_contr *contr)
{
	// printf("ICI\n");
	char **output;
	int i;
	int cpt;
	int fd;

	fd = open(filename,O_RDONLY);
	output = malloc(sizeof(char *) * 100);
	i = 1;
	cpt = 0;
	while(i > 0)
		i = get_next_line(fd, &(output[cpt++]));
	output[cpt] = ft_strdup("\0");
	i = 0;
	// printf("icic\n");
	while(i < cpt)
	{
		if(output[i][0] == 'R' || output[i][0] == 'r')
		{
			get_res(output[i], contr);
			// int w = ft_atoi();
		}
		// printf("ici\n");
		printf("%s\n",output[i++]);
	}
	close(fd);
}

void parse(char **in, t_contr *contr)
{

	int size = contr->map_w;

	int **map;

	map = malloc(sizeof(int*) * size);

	int i = 0;
	int j = 0;
	while(i < size)
	{
		map[i] = malloc(sizeof(int) * size);
		while(j < size)
		{
			if(in[i][j] != '0' && in[i][j] != '1' && in[i][j] != '3' )
			{
				write(1,"UNVALID MAP FILE ICI",20);
				exit(0);
			}
			if (in[i][j] == '3')
			{
				// contr->p_y = (double)i +0.5; 
				// contr->p_x = (double)j + 0.5;
				printf("PY = %d PX = %d \n",i,j );
				map[i][j] = 0;
			}
			else
				map[i][j] = in[i][j] - '0';
			j++;
		}
		j = 0;
		i++;
	}
	printf("LOADED MAP : \n");
	for(int p = 0; p < size; p++)
	{
		for(int z = 0; z < size; z++ )
			printf("|%d|",map[p][z]);
		printf("\n");
	}
	contr->map = map;
}

void load_map(char *filename, t_contr *contr)
{
	char *line;
	char **output;

	int fd;

	output = malloc(sizeof(char *) * 100);
	fd = open(filename,O_RDONLY);
	int i;
	
	int size;
	size = 0;
	int cpt = 0;
	i = 1;
	while(i && cpt < 100)
	{
		i = get_next_line(fd, &(output[cpt]));
		cpt++;
	}
	cpt--;
	for(int j = 0; j < cpt; j++)
	{
		if(j == 0)
		{
			size = ft_atoi(output[j]);
			// size = output[j][0] - '0';
			free(output[j]);
			output++;
		}
	}
	if(cpt != size)
	{
		printf("CPT = %d size = %d", cpt,size);
		write(1,"UNVALID MAP FILE",16);
		exit(0);
	}
	contr->map_w = size;
	parse(output, contr);
}