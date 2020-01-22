/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:12:40 by edal--ce          #+#    #+#             */
/*   Updated: 2020/01/22 04:42:21 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
		return (1);
	return (0);
}

int	ft_atoi(const char *in)
{
	int pos;
	int nb;

	nb = 0;
	pos = 1;
	while (*in == ' ' || *in == '	' || *in == '\n'
		|| *in == '\t' || *in == '\v' || *in == '\f' || *in == '\r')
		in++;
	if (*in == '-')
	{
		pos = -1;
		in++;
	}
	else if (*in == '+')
		in++;
	while (ft_isdigit(*in))
		nb = nb * 10 + (*(in++) - '0');
	return (nb * pos);
}
