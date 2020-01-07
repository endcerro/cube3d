/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:05 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/29 19:27:24 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_buff(char *cache, char *s2)
{
	char	*out;
	char	*cp;
	int		size;

	size = 1;
	size += ft_strlen(cache) + BUFFER_SIZE;
	if (!cache && !s2)
		return (NULL);
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	cp = out;
	size = 0;
	if (cache != NULL)
		while (cache[size])
			*(out++) = cache[size++];
	size = 0;
	while (size < BUFFER_SIZE)
		*(out++) = s2[size++];
	*out = '\0';
	if (cache != NULL)
		free(cache);
	return (cp);
}

static void	refresh_cache(char **cache)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	while ((*cache)[i] != '\n' && (*cache)[i] != '\0')
		i++;
	if (!(out = malloc(sizeof(char) * (ft_strlen(*cache) - i + 1))))
		return ;
	while ((*cache)[++i] != '\0')
		out[j++] = (*cache)[i];
	out[j] = '\0';
	free(*cache);
	*cache = out;
}

static char	*get_line_from_cache(char **cache, int *read_status)
{
	int		i;
	char	*out;
	int		j;

	if (cache == NULL)
		return (NULL);
	out = NULL;
	j = -1;
	i = ft_strchr_int(*cache, '\n');
	if (i != -1)
		*read_status = 1;
	if (*read_status == 0 && i == -1)
		i = ft_strchr_int(*cache, '\0');
	if (i != -1)
	{
		if (!(out = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		while (++j < i)
			out[j] = (*cache)[j];
		out[j] = '\0';
		refresh_cache(cache);
	}
	return (out);
}

static int	just_two_more_lines_plz(char **line)
{
	*line = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE];
	static char	*cache;
	int			read_status;

	if (BUFFER_SIZE == 0 || fd == -1 || line == NULL)
		return (-1);
	read_status = 1;
	*line = NULL;
	while (*line == NULL && read_status > 0)
	{
		initbfr(buffer);
		if ((read_status = read(fd, buffer, BUFFER_SIZE)) == 0 && cache == NULL)
			return (just_two_more_lines_plz(line));
		cache = ft_strjoin_buff(cache, buffer);
		*line = get_line_from_cache(&cache, &read_status);
	}
	if (read_status == 0 && cache != NULL)
	{
		free(cache);
		cache = NULL;
	}
	if (*line == NULL)
		*line = ft_strdup("");
	return (read_status);
}
