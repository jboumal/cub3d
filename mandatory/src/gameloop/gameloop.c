/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 12:30:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	translate_cam(t_game *game)
{
	t_vector	*pos;
	t_vector	dir;
	t_vector	pos_up;
	t_vector	pos_down;

	pos = &game->player.pos;
	dir = game->player.dir;
	pos_up = vector(pos->x + dir.x * MOVE_SPEED, pos->y + dir.y * MOVE_SPEED);
	pos_down = vector(pos->x - dir.x * MOVE_SPEED, pos->y - dir.y * MOVE_SPEED);
	if (game->state.up)
	{
		if (!game->map.data[(int)pos->y * game->map.width + (int)pos_up.x])
			pos->x = pos_up.x;
		if (!game->map.data[(int)pos_up.y * game->map.width + (int)pos->x])
			pos->y = pos_up.y;
	}
	if (game->state.down)
	{
		if (!game->map.data[(int)pos->y * game->map.width + (int)pos_down.x])
			pos->x = pos_down.x;
		if (!game->map.data[(int)pos_down.y * game->map.width + (int)pos->x])
			pos->y = pos_down.y;
	}
}

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
	translate_cam(game);
	rotate_cam(game);
}

int	game_loop(t_game *game)
{
	game_update(game);
	render(game);
	return (0);
}
