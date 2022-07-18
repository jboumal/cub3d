/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:05:59 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 13:19:49 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, SCREEN_TITLE);
	game->state.up = false;
	game->state.left = false;
	game->state.down = false;
	game->state.right = false;
}

int	quit(void *args)
{
	(void) args;
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (0);
	initialize(&game);
	parser(argc, argv, &game);
	mlx_hook(game.window, K_RELEASE_EVENT, K_RELEASE_MASK, key_release, &game);
	mlx_hook(game.window, K_PRESS_EVENT, K_PRESS_EVENT, key_down, &game);
	mlx_hook(game.window, DESTROY_NOTIFY_EVENT, NO_EVENT_MASK, quit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
