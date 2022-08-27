/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 08:39:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 18:29:09 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map.floor = -1;
	game->map.ceil = -1;
	game->mlx = mlx_init();
	game->state.m_left = 0;
	game->state.m_right = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	initialize(&game);
	parse(argc, argv, &game);
	game.window = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, SCREEN_TITLE);
	mlx_hook(game.window, K_RELEASE_EVENT, K_RELEASE_MASK, key_release, &game);
	mlx_hook(game.window, K_PRESS_EVENT, K_PRESS_EVENT, key_down, &game);
	mlx_hook(game.window, DESTROY_NOTIFY_EVENT, NO_EVENT_MASK, quit, &game);
	if (MAC)
		mlx_hook(game.window, MOUSE_MOVE, NO_EVENT_MASK, mouse_hook, &game);
	mouse_hide(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
