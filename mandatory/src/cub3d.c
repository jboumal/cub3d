/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:05:59 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 21:51:45 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, SCREEN_TITLE);
	load_textures(game);
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

	mlx_hook(game.window, K_RELEASE_EVENT, 1L << 0, key_release, &game);
	mlx_hook(game.window, K_PRESS_EVENT, 1L << 1, key_down, &game);
	mlx_hook(game.window, DESTROY_NOTIFY_EVENT, 1L, quit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
