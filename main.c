/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:26:15 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/26 19:36:50 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"

void	draw_hp(t_contr *contr)
{
	t_vpi	t;
	t_vpi	t2;

	t.y = contr->res.y - 100;
	t.x = 10;
	t2.x = 0.25 * 1000;
	t2.y = 40;
	draw_square_i(contr, t, t2, 0x00000000);
	t2.x = 0.25 * contr->hp;
	if (contr->hp > 750)
		draw_square_i(contr, t, t2, 0x0000FF00);
	else if (contr->hp > 500)
		draw_square_i(contr, t, t2, 0x00FFFF00);
	else if (contr->hp > 250)
		draw_square_i(contr, t, t2, 0x00FFA500);
	else
		draw_square_i(contr, t, t2, 0x00FF0000);
	if (contr->hp == 0)
		close_(contr, 0);
}

#ifdef BONUS

int		loop_(void *params)
{
	t_contr *contr;

	contr = (t_contr*)params;
	if (contr->menu_mode == 0)
	{
		wall_cast((t_contr*)params);
		move_spr(params);
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

#else

int		loop_(void *params)
{
	wall_cast((t_contr*)params);
	handle_keys((t_contr*)params);
	print_image((t_contr*)params, 0, 0);
	return (0);
}

#endif

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
}

int		main(int argc, char **argv)
{
	t_contr contr;

	init_game(&contr);
	if (argc < 2)
		close_(&contr, "Please state the path of the map");
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		contr.screen = 1;
	else
		contr.screen = 0;
	load_cub(argv[1], &contr);
	prep_game(&contr);
	load_wpns(&contr);
	mlx_do_key_autorepeaton(contr.mlx);
	mlx_hook(contr.win_ptr, 17, 0, close_, (void *)&contr);
	mlx_hook(contr.win_ptr, 2, 0, key_press, (void *)&contr);
	mlx_hook(contr.win_ptr, 3, 0, key_release, (void *)&contr);
	mlx_mouse_hook(contr.win_ptr, mouse_, (void *)&contr);
	mlx_loop_hook(contr.mlx, loop_, (void *)&contr);
	mlx_loop(contr.mlx);
	return (0);
}
