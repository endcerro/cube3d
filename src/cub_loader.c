/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:41:01 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 13:14:44 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"
#include <fcntl.h>

void	get_res(char *line, t_contr *contr)
{
	int		height;
	int		width;
	int		offset;
	int		x;
	int		y;

	offset = 1;
	height = ft_atoi(line + offset++);
	while (ft_isspace(line[offset]))
		offset++;
	while (ft_isdigit(line[offset]))
		offset++;
	width = ft_atoi(line + offset);
	if (width <= 0 || height <= 0 || contr->map_parser.res == 1)
		close_(contr, "Error\nGETTING RESOLUTION");
	mlx_get_screen_size(contr->mlx, &x, &y);
	contr->res.x = (width > x) ? x : width;
	contr->res.y = (height > y) ? y : height;
	contr->map_parser.res = 1;
}

void	parseline(char *line, t_contr *contr, int *val)
{
	if (*line == '\n' || *line == 0)
		*val = *val - 1;
	else if (*line == 'R')
		get_res(line, contr);
	else if (*line == 'N' && line[1] == 'O')
		get_text_no(line, contr);
	else if (*line == 'S' && line[1] == 'O')
		get_text_so(line, contr);
	else if (*line == 'W' && line[1] == 'E')
		get_text_we(line, contr);
	else if (*line == 'E' && line[1] == 'A')
		get_text_ea(line, contr);
	else if (*line == 'S')
		get_text_spr(line, contr);
	else if (*line == 'F')
		get_fc_colors(line, contr);
	else if (*line == 'C')
		get_fc_colors(line, contr);
	else
		close_(contr, "Error \nPARSING");
	*val = *val + 1;
	free(line);
}

int		read_map(t_contr *contr, int p, int fd)
{
	int		read;
	char	**map;

	if (!(map = malloc(sizeof(char*) * 100)))
		close_(contr, "Error \nFAILED MALLOC");
	read = 1;
	while (read && p == 0)
	{
		read = get_next_line(fd, &map[p]);
		if (map[p][0] == 0)
			free(map[p]);
		else
			p++;
	}
	while (read && p < 100)
		read = get_next_line(fd, &map[p++]);
	contr->map = map;
	if (p == 100)
		close_(contr, "Error \nMAP TOO BIG");
	return (p);
}

void	load_map(t_contr *contr, int fd)
{
	int		p;
	int		i;

	i = -1;
	p = 0;
	p = read_map(contr, p, fd);
	contr->mpd = set_vpi(ft_strlen(contr->map[0]), p);
	while (++i < contr->mpd.y)
	{
		if (contr->map[i][0] == 0 && contr->mpd.y)
		{
			free_after(contr, i);
			break ;
		}
		sub_load(contr, i);
	}
	if (contr->pos.x < 0 || contr->pos.y < 0)
		close_(contr, "Error\nINVALID MAP");
	parse_map(contr);
	parse_sprites(contr);
	close(fd);
}

void	load_cub(char *filename, t_contr *contr)
{
	char	*line;
	int		fd;
	int		read;
	int		val;
	int		end;

	end = ft_strlen(filename) - 1;
	if (filename[end] != 'b' || filename[end - 1] != 'u' ||
		filename[end - 2] != 'c' || filename[end - 3] != '.')
		close_(contr, "Error \nWRONG FILE EXTENSION");
	fd = open(filename, O_RDONLY);
	if (fd < 1)
		close_(contr, "Error \nWRONG MAP PATH");
	read = 1;
	val = 0;
	while (read && val < 8)
	{
		read = get_next_line(fd, &line);
		parseline(line, contr, &val);
	}
	check_init(contr);
	load_map(contr, fd);
}
