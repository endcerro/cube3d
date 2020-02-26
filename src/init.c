/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:44:35 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 06:50:38 by edal--ce         ###   ########.fr       */
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

void	texture_loadr(char *path, t_contr *contr, int index)
{
	t_text *texture;

	if (index == -1)
		index = contr->tx_nb;
	texture = &(contr->textures[index]);
	texture->texture.img = mlx_xpm_file_to_image(contr->mlx, path, &texture->w,
		&texture->h);
	if (texture->texture.img == 0)
		close_(contr, "Error \nTEXTURE NOT FOUND");
	texture->texture.addr = mlx_get_data_addr(texture->texture.img, &(texture->
		texture.bpp), &(texture->texture.length), &(texture->texture.endian));
	contr->tx_nb++;
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
	init_keys(contr);
	texture_loadr("textures/new_floor.xpm", contr, -1);
	texture_loadr("textures/TOFIX.xpm", contr, -1);
	texture_loadr("textures/pghost.xpm", contr, -1);
	texture_loadr("textures/MENU.xpm", contr, -1);
}

int		close_(t_contr *contr, char *message)
{
	int i;

	write(1, message, ft_strlen(message));
	free_mand(contr);
	i = 4;
	while (++i < contr->tx_nb - 1)
		mlx_destroy_image(contr->mlx, contr->textures[i].texture.img);
	i = -1;
	while (++i < contr->mpd.y)
		free(contr->map[i]);
	if (contr->pos.x != -1)
		free(contr->mlx);
	free(contr->map);
	system("leaks a.out");
	exit(0);
	return (0);
}

void	load_wpns(t_contr *contr)
{
	t_text *tx;

	tx = &(contr->weapons[0]);
	tx->texture.img = mlx_xpm_file_to_image(contr->mlx,
		"textures/attack_idle.xpm", &tx->w, &tx->h);
	if (tx->texture.img == 0)
		close_(contr, "Error \nTEXTURE NOT FOUND\n");
	tx->texture.addr = mlx_get_data_addr(tx->texture.img, &(tx->texture.bpp),
		&(tx->texture.length), &(tx->texture.endian));
	tx = &(contr->weapons[1]);
	tx->texture.img = mlx_xpm_file_to_image(contr->mlx,
		"textures/attack_on.xpm", &tx->w, &tx->h);
	if (tx->texture.img == 0)
		close_(contr, "Error \nTEXTURE NOT FOUND\n");
	tx->texture.addr = mlx_get_data_addr(tx->texture.img, &(tx->texture.bpp),
		&(tx->texture.length), &(tx->texture.endian));
}
