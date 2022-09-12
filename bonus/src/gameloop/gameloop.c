/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/12 19:11:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps_counter(t_game *g)
{
	static int		n_frame = 0;
	static int		second = 0;
	struct timeval	t;

	n_frame++;
	gettimeofday(&t, NULL);
	if (t.tv_sec > second)
	{
		g->fps = n_frame;
		n_frame = 0;
		second = t.tv_sec;
	}
}

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
		while (i < TEXTURES_MAX)
		{
			clst_rotate(&g->textures[i]);
			i++;
		}
	}
	accu++;
}

static void	game_update(t_game *game)
{
	translate_cam(game);
	rotate_cam(game);
	update_doors(game);
	update_textures(game);
	collect_items(game);
}

int	game_loop(t_game *game)
{
	fps_counter(game);
	if (LINUX)
		my_mouse_hook(game);
	game_update(game);
	render(game);
	return (0);
}
