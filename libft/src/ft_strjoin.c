/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:48:53 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/18 07:28:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	char	*cp;
	int		sz;

	sz = 1;
	if (s1)
		sz += ft_strlen(s1);
	if (s2)
		sz += ft_strlen(s2);
	if (!s1 && !s2)
		return (0);
	if (!(out = malloc(sizeof(char) * sz)))
		return (0);
	cp = out;
	if (s1--)
		while (*(++s1))
			*(out++) = *s1;
	if (s2--)
		while (*(++s2))
			*(out++) = *s2;
	*out = 0;
	return (cp);
}

char	*ft_strjoin_fill(char const *s1, char c, int n)
{
	char	*out;
	char	*cp;
	int		sz;
	int		i;

	i = -1;
	sz = 1;
	if (s1)
		sz += ft_strlen(s1);
	sz += n;
	if (!(out = malloc(sizeof(char) * sz)))
		return (0);
	cp = out;
	if (s1--)
		while (*(++s1))
			*(out++) = *s1;
	while (++i < n)
		*(out++) = c;
	*out = 0;
	return (cp);
}
