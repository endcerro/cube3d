/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:44:35 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/14 07:51:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	init_keys(t_contr *contr)
{
	contr->key.w = 0;
	contr->key.a = 0;
	contr->key.s = 0;
	contr->key.d = 0;
	contr->key.q = 0;
	contr->key.e = 0;
}

void	prep_game(t_contr *contr)
{
	t_img image;

	contr->win_ptr = mlx_new_window(contr->mlx, contr->res.x, contr->res.y,
		"cub3d");
	image.img = mlx_new_image(contr->mlx, contr->res.x, contr->res.y);
	image.addr = mlx_get_data_addr(image.img, &(image.bpp), &(image.length),
		&(image.endian));
	contr->img = image;
	contr->sett.move_speed = 5;
	contr->sett.rot_speed = 5;
	contr->sett.fov = 5;
	contr->atk_frame = 0;
	contr->hp = 1000;
	contr->menu_mode = 0;
	contr->dark_mode = 0;
	contr->score = 0;
	init_keys(contr);
}

void	init_game(t_contr *contr)
{
	int i;

	i = -1;
	while (++i < 5)
		contr->basic_sprites[i] = 0;
	contr->mlx = mlx_init();
	contr->tx_nb = 0;
	contr->win_ptr = 0;
	contr->enn_id = -1;
	contr->sprites_nb = 0;
	contr->pos.x = -1;
	contr->mpd.y = 0;
	contr->map = 0;
}

void	load_wpns(t_contr *contr)
{
	t_text *tx;

	tx = &(contr->weapons[0]);
	tx->texture.img = mlx_xpm_file_to_image(contr->mlx,
		"textures/attack_idle.xpm", &tx->w, &tx->h);
	if (tx->texture.img == 0)
		close_(contr, "Error \nTEXTURE NOT FOUND B\n");
	tx->texture.addr = mlx_get_data_addr(tx->texture.img, &(tx->texture.bpp),
		&(tx->texture.length), &(tx->texture.endian));
	tx = &(contr->weapons[1]);
	tx->texture.img = mlx_xpm_file_to_image(contr->mlx,
		"textures/attack_on.xpm", &tx->w, &tx->h);
	if (tx->texture.img == 0)
		close_(contr, "Error \nTEXTURE NOT FOUND B\n");
	tx->texture.addr = mlx_get_data_addr(tx->texture.img, &(tx->texture.bpp),
		&(tx->texture.length), &(tx->texture.endian));
}
