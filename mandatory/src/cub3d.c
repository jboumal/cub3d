/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:05:59 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/03 07:32:49 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_game *game)
{
	memset(game, 0, sizeof(t_game));
	game->map.floor = -1;
	game->map.ceil = -1;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, SCREEN_TITLE);
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
	parser(argv, &game);
	mlx_hook(game.window, K_RELEASE_EVENT, K_RELEASE_MASK, key_release, &game);
	mlx_hook(game.window, K_PRESS_EVENT, K_PRESS_EVENT, key_down, &game);
	mlx_hook(game.window, DESTROY_NOTIFY_EVENT, NO_EVENT_MASK, quit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
