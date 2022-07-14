/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:16:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 13:55:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	translate_cam(t_game *game)
{
	t_vector	*pos;
	t_vector	dir;
	t_vector	np;

	pos = &game->player.pos;
	dir = game->player.dir;
	if (game->state.up)
	{
		np = vector(pos->x + dir.x * MOVE_SPEED, pos->y + dir.y * MOVE_SPEED);
		if (!game->map.data[(int)pos->y * game->map.width + (int)np.x])
			pos->x = np.x;
		if (!game->map.data[(int)np.y * game->map.width + (int)pos->x])
			pos->y = np.y;
	}
	if (game->state.down)
	{
		np = vector(pos->x - dir.x * MOVE_SPEED, pos->y - dir.y * MOVE_SPEED);
		if (!game->map.data[(int)pos->y * game->map.width + (int)np.x])
			pos->x = np.x;
		if (!game->map.data[(int)np.y * game->map.width + (int)pos->x])
			pos->y = np.y;
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
