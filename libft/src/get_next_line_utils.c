/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:49 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 12:26:41 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

void	initbfr(char *buff)
{
	int i;

	i = 0;
	while (i < BUFFER_SIZE)
		buff[i++] = '\0';
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
