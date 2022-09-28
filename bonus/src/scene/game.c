/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:25:54 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/12 18:36:10 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_doors(t_game *g)
{
	t_vector	cell;
	t_node		*node;
	t_door		*door;

	node = g->doors.head;
	while (node)
	{
		door = node->content;
		cell = vector(door->cell % g->map.width, door->cell / g->map.width);
		door->opened &= !(vector_norme(vector_sub(cell, g->player.pos)) > 5);
		if (!door->opened && door->ratio < 1)
			door->ratio += 0.01;
		if (door->opened && door->ratio > 0.1)
			door->ratio -= 0.01;
		node = node->next;
	}
}

static void	update_textures(t_game *g)
{
	static int	accu;
	int			i;

	if (!(accu % 10))
	{
		i = 0;
		while (i < WALL_MAX)
		{
			if (g->walls[i].img)
			{
				clst_rotate(&g->walls[i].imgs);
				g->walls[i].img = g->walls[i].imgs.head->content;
			}
			i++;
		}
	}
	accu++;
}

void	game_update(t_game *game)
{
	translate_cam(game);
	rotate_cam(game);
	update_doors(game);
	update_textures(game);
}