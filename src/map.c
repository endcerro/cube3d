#include "../header/header.h"
#include <fcntl.h>




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
				contr->p_y = (double)i;
				contr->p_x = (double)j;
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
	
	//i = 0;
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
			size = output[j][0] - '0';
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
	//printf("cpt = %d\n",cpt );
	contr->map_w = size;
	parse(output, contr);
	//return((int**)output);
}