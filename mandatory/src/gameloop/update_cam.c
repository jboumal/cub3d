/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:16:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 14:31:27 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	translate_cam(t_game *g)
{
	t_vector	*pos;
	t_vector	dir;
	t_vector	np;

	pos = &g->player.pos;
	dir = g->player.dir;
	if (g->state.up)
	{
		np = vector(pos->x + dir.x * MOVE_SPEED, pos->y + dir.y * MOVE_SPEED);
		if (!g->map.data[(int)pos->y * g->map.width + (int)np.x])
			pos->x = np.x;
		if (!g->map.data[(int)np.y * g->map.width + (int)pos->x])
			pos->y = np.y;
	}
	if (g->state.down)
	{
		np = vector(pos->x - dir.x * MOVE_SPEED, pos->y - dir.y * MOVE_SPEED);
		if (!g->map.data[(int)pos->y * g->map.width + (int)np.x])
			pos->x = np.x;
		if (!g->map.data[(int)np.y * g->map.width + (int)pos->x])
			pos->y = np.y;
	}
}

void	rotate_cam(t_game *g)
{
	if (g->state.left)
	{
		g->player.dir = vector_rotate(g->player.dir, ROT_SPEED);
		g->player.plane = vector_rotate(g->player.plane, ROT_SPEED);
	}
	if (g->state.right)
	{
		g->player.dir = vector_rotate(g->player.dir, -ROT_SPEED);
		g->player.plane = vector_rotate(g->player.plane, -ROT_SPEED);
	}
}
