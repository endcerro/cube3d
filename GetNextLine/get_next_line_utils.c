/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:49 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/23 16:04:51 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*p;

	if (!(p = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	p[i] = 0;
	return (p);
}

void	initbfr(char *buff)
{
	int i;

	i = 0;
	while (i < BUFFER_SIZE)
		buff[i++] = '\0';
}

int		ft_strlen(char *str)
{
	int cpt;

	if (str == NULL)
		return (0);
	cpt = 0;
	while (str[cpt])
		cpt++;
	return (cpt);
}

int		ft_strchr_int(const char *str, int c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	if (str[i] == c)
		return (i);
	return (-1);
}
