/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:41:01 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 00:06:49 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"
#include <fcntl.h>

int		parse_map(t_contr *contr)
{
	int i;

	i = -1;
	while (++i < contr->mpd.x)
	{
		if (contr->map[0][i] != '1' || contr->map[contr->mpd.y - 1][i] != '1')
			close_(contr, "MAP NOT CLOSED\n");
	}
	i = -1;
	while (++i < contr->mpd.y)
	{
		if (contr->map[i][0] != '1' || contr->map[i][contr->mpd.x - 1] != '1')
			close_(contr, "MAP NOT CLOSED\n");
	}
	return (1);
}

void	parse_sprites(t_contr *contr)
{
	int			i;
	int			j;
	int			*sprite_nb;
	t_sprite	*sprites;

	i = -1;
	j = 0;
	sprites = (contr->sprites);
	sprite_nb = &(contr->sprites_nb);
	while (++i < contr->mpd.y)
	{
		j = -1;
		while (++j < contr->mpd.x)
		{
			if (contr->map[i][j] == '2' || contr->map[i][j] == '3')
			{
				sprites[*sprite_nb].y = i + 0.5;
				sprites[*sprite_nb].x = j + 0.5;
				sprites[*sprite_nb].texture = contr->textures[4];
				if (contr->map[i][j] == '3')
					contr->enn_id = *sprite_nb;
				(*sprite_nb)++;
			}
		}
	}
}

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

double	get_fov(t_contr *contr)
{
	return (0.50 / (1.0 * contr->res.y / (1.0 * contr->res.x)));
}

void	load_map(t_contr *contr, int fd)
{
	char	**map;
	int		p;
	int		read;
	t_vp	pos;
	int		i;
	int		j;

	i = -1;
	p = 0;
	read = 1;
	if (!(map = malloc(sizeof(char*) * 100)))
		close_(contr, "FAILED MALLOC");
	while (read)
		read = get_next_line(fd, &map[p++]);
	contr->pos.x = -1;
	contr->mpd.x = ft_strlen(map[0]);
	contr->mpd.y = p;
	contr->map = map;
	while (++i < contr->mpd.y)
	{
		if ((int)ft_strlen(map[i]) != contr->mpd.x)
			close_(contr, "ERROR PARSING");
		j = -1;
		while (++j < contr->mpd.x)
		{
			if (map[i][j] == 'N' && contr->pos.x == -1)
				set_n(contr, i, j);
			else if (map[i][j] == 'S' && contr->pos.x == -1)
				set_s(contr, i, j);
			else if (map[i][j] == 'E' && contr->pos.x == -1)
				set_e(contr, i, j);
			else if (map[i][j] == 'W' && contr->pos.x == -1)
				set_w(contr, i, j);
		}
	}
	if (contr->pos.x == -1 || contr->pos.y == -1)
		close_(contr, "NO POS IN MAP ERROR\n");
	parse_map(contr);
	parse_sprites(contr);
}

void	init_vals(t_contr *contr)
{
	contr->res.x = -1;
	contr->res.y = -1;
}

int		check_vals(t_contr *contr)
{
	if (contr->res.x == -1 || contr->res.y == -1)
		close_(contr, "ERROR PARSING MISSING VALUES\n");
	if (contr->text_nb != 5)
		close_(contr, "ERROR PARSING MISSING VALUES\n");
	return (1);
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
	check_vals(contr);
}
