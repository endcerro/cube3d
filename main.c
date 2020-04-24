/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:26:15 by edal--ce          #+#    #+#             */
/*   Updated: 2020/04/24 12:02:05 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"

#ifdef BONUS

int		loop_(void *params)
{
	t_contr *contr;

	contr = (t_contr*)params;
	if (contr->menu_mode == 0)
	{
		wall_cast((t_contr*)params);
		move_enn(params);
		handle_keys((t_contr*)params);
		draw_minmap((t_contr*)params);
		draw_hp((t_contr*)params);
		draw_wpn((t_contr*)params);
		print_image((t_contr*)params, 0, 0);
	}
	else
		menu_mode(contr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_contr contr;

	init_game(&contr, 1);
	if (argc < 2)
		close_(&contr, "Please state the path of the map");
	contr.screen = 0;
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		contr.screen = 1;
	load_cub(argv[1], &contr);
	texture_loadr("src/textures/new_floor.xpm", &contr, -1);
	texture_loadr("src/textures/new_ceil.xpm", &contr, -1);
	texture_loadr("src/textures/pghost.xpm", &contr, -1);
	texture_loadr("src/textures/MENU.xpm", &contr, -1);
	prep_game(&contr);
	load_wpns(&contr);
	mlx_do_key_autorepeaton(contr.mlx);
	mlx_hook(contr.win_ptr, KeyPress, KeyPressMask, key_press, (void *)&contr);
	mlx_hook(contr.win_ptr, KeyRelease, KeyReleaseMask,
		key_release, (void *)&contr);
	mlx_mouse_hook(contr.win_ptr, mouse_, (void *)&contr);
	mlx_loop_hook(contr.mlx, loop_, (void *)&contr);
	mlx_hook(contr.win_ptr, DestroyNotify, StructureNotifyMask,
		close_hook, (void *)&contr);
	mlx_loop(contr.mlx);
	return (0);
}

#else

int		loop_(void *params)
{
	wall_cast((t_contr*)params);
	handle_keys((t_contr*)params);
	print_image((t_contr*)params, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_contr contr;

	init_game(&contr, 0);
	if (argc < 2)
		close_(&contr, "Please state the path of the map");
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		contr.screen = 1;
	else
		contr.screen = 0;
	load_cub(argv[1], &contr);
	prep_game(&contr);
	mlx_do_key_autorepeaton(contr.mlx);
	mlx_hook(contr.win_ptr, KeyPress, KeyPressMask, key_press, (void *)&contr);
	mlx_hook(contr.win_ptr, KeyRelease, KeyReleaseMask,
		key_release, (void *)&contr);
	mlx_mouse_hook(contr.win_ptr, mouse_, (void *)&contr);
	mlx_loop_hook(contr.mlx, loop_, (void *)&contr);
	mlx_hook(contr.win_ptr, DestroyNotify, StructureNotifyMask,
		close_hook, (void *)&contr);
	mlx_loop(contr.mlx);
	return (0);
}

#endif

int		close_(t_contr *contr, char *message)
{
	int i;

	i = write(1, message, ft_strlen(message));
	i = 5;
	free_mand(contr);
	while (i < contr->tx_nb)
		mlx_destroy_image(contr->mlx, contr->textures[i++].texture.img);
	i = -1;
	while (++i < contr->mpd.y)
		free(contr->map[i]);
	if (contr->bonus == 1 && contr->score != -1)
	{
		mlx_destroy_image(contr->mlx, contr->weapons[0].texture.img);
		mlx_destroy_image(contr->mlx, contr->weapons[1].texture.img);
	}
	if (contr->win_ptr != 0)
	{
		mlx_destroy_image(contr->mlx, contr->img.img);
		mlx_destroy_window(contr->mlx, contr->win_ptr);
		free(contr->mlx);
	}
	free(contr->map);
	exit(0);
	return (0);
}
