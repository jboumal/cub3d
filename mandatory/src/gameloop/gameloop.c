/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 11:39:04 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	rotate_cam(t_game *game)
{
	if (game->state.left)
	{
		game->player.dir = vector_rotate(game->player.dir, ROT_SPEED);
		game->player.plane = vector_rotate(game->player.plane, ROT_SPEED);
	}
	if (game->state.right)
	{
		game->player.dir = vector_rotate(game->player.dir, -ROT_SPEED);
		game->player.plane = vector_rotate(game->player.plane, -ROT_SPEED);
	}
}

void	game_update(t_game *game)
{
	rotate_cam(game);
}

int	game_loop(t_game *game)
{
	game_update(game);
	render(game);
	return (0);
}
