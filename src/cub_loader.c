/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:41:01 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 01:31:07 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"
#include <fcntl.h>

void	get_res(char *line, t_contr *contr)
{
	int		height;
	int		width;
	int		offset;

	offset = 1;
	height = ft_atoi(line + offset++);
	while (ft_isdigit(line[offset]))
		offset++;
	width = ft_atoi(line + offset);
	if (width <= 0 || height <= 0)
		close_(contr, "ERROR IN GETTING RESOLUTION");
	contr->res.x = (width > 2560) ? 2560 : width;
	contr->res.y = (height > 1440) ? 1440 : height;
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
		while (ft_isdigit(line[offset]))
			offset++;
		offset++;
		c.g = ft_atoi(line + offset);
		while (ft_isdigit(line[offset]))
			offset++;
		offset++;
		c.b = ft_atoi(line + offset);
	}
	if (c.b == -1 || c.r == -1 || c.g == -1)
		close_(contr, "ERROR READING COLORS\n");
	if (*line == 'F')
		contr->f_color = (c.r << 16) | (c.g << 8) | c.b;
	else if (*line == 'C')
		contr->c_color = (c.r << 16) | (c.g << 8) | c.b;
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
	*val = *val + 1;
	free(line);
}

void	load_map(t_contr *contr, int fd)
{
	char	**map;
	int		p;
	int		read;
	int		i;

	i = -1;
	p = 0;
	read = 1;
	if (!(map = malloc(sizeof(char*) * 100)))
		close_(contr, "FAILED MALLOC");
	while (read)
		read = get_next_line(fd, &map[p++]);
	contr->mpd = set_vpi(ft_strlen(map[0]), p);
	contr->map = map;
	while (++i < contr->mpd.y)
	{
		if ((int)ft_strlen(map[i]) != contr->mpd.x)
			close_(contr, "ERROR PARSING");
		sub_load(contr, i);
	}
	if (contr->pos.x < 0 || contr->pos.y < 0)
		close_(contr, "NO POS IN MAP ERROR\n");
	parse_map(contr);
	parse_sprites(contr);
}

void	load_cub(char *filename, t_contr *contr)
{
	char	*line;
	int		fd;
	int		read;
	int		val;

	fd = open(filename, O_RDONLY);
	read = 1;
	val = 0;
	while (read && val < 8)
	{
		read = get_next_line(fd, &line);
		parseline(line, contr, &val);
	}
	load_map(contr, fd);
}
