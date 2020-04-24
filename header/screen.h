/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:59:32 by user42            #+#    #+#             */
/*   Updated: 2020/04/14 17:11:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

# pragma pack(1)

typedef struct		s_bmp_fhead
{
	unsigned char	type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset;
}					t_bmp_fhead;

typedef struct		s_bmp_ihead
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bmp_ihead;

#endif
