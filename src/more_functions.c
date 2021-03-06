/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:23:25 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/23 17:15:57 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

t_vp	set_vp(double x, double y)
{
	t_vp out;

	out.x = x;
	out.y = y;
	return (out);
}

t_vpi	set_vpi(int x, int y)
{
	t_vpi out;

	out.x = x;
	out.y = y;
	return (out);
}

int		vpi_norm(t_vpi v)
{
	return (abs(v.x) + abs(v.y));
}

double	vp_norm(t_vp v)
{
	return (fabs(v.x) + fabs(v.y));
}

void	free_after(t_contr *contr, int i)
{
	int j;

	j = 0;
	while (i + j < contr->mpd.y)
		free(contr->map[i + j++]);
	contr->mpd.y -= j;
}
