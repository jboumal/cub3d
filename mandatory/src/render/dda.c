/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:01:48 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 14:27:39 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	get_side_dist(
				t_vector ray_dir,
				int cell,
				t_vector delta_dist,
				t_game *g)
{
	t_vector	pos;
	t_vector	side_dist;

	pos = g->player.pos;
	if (ray_dir.x < 0)
		side_dist.x = (pos.x - cell % g->map.width) * delta_dist.x;
	else
		side_dist.x = (cell % g->map.width + 1.0 - pos.x) * delta_dist.x;
	if (ray_dir.y < 0)
		side_dist.y = (pos.y - cell / g->map.width) * delta_dist.y;
	else
		side_dist.y = (cell / g->map.width + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}

double	dda(t_vector ray_dir, t_face *face, t_game *g)
{
	t_vector	delta_dist;
	t_vector	side_dist;

	face->cell = (int)g->player.pos.y * g->map.width + (int)g->player.pos.x;
	delta_dist = vector(1 / fabs(ray_dir.x), 1 / fabs(ray_dir.y));
	side_dist = get_side_dist(ray_dir, face->cell, delta_dist, g);
	while (!g->map.data[face->cell])
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			face->cell += -2 * (ray_dir.x < 0) + 1;
			face->side = W * (ray_dir.x <= 0) + E * (ray_dir.x > 0);
		}
		else
		{
			side_dist.y += delta_dist.y;
			face->cell += -2 * g->map.width * (ray_dir.y < 0) + g->map.width;
			face->side = N * (ray_dir.y >= 0) + S * (ray_dir.y < 0);
		}
	}
	if (face->side % 2)
		return (side_dist.x - delta_dist.x);
	return (side_dist.y - delta_dist.y);
}
