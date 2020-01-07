/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:58 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/23 16:05:00 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <stdio.h>

# include <unistd.h>

char	*ft_strdup(char *s1);
void	initbfr(char *buff);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
int		ft_strchr_int(const char *str, int c);

#endif
