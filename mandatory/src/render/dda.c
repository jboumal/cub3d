/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:01:48 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/13 13:59:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector
	get_side_dist(t_vector ray_dir, int cell, t_vector delta_dist, t_game *game)
{
	t_vector	pos;
	t_vector	side_dist;

	pos = game->player.pos;
	if (ray_dir.x < 0)
		side_dist.x = (pos.x - cell % game->map.width) * delta_dist.x;
	else
		side_dist.x = (cell % game->map.width + 1.0 - pos.x) * delta_dist.x;
	if (ray_dir.y < 0)
		side_dist.y = (pos.y - cell % game->map.width) * delta_dist.y;
	else
		side_dist.y = (cell / game->map.width + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}

double	dda(t_vector ray_dir, t_game *game)
{
	int			cell;
	t_vector	delta_dist;
	t_vector	side_dist;
	int			step_x;
	int			step_y;

	cell = (int)game->player.pos.y * game->map.width + (int)game->player.pos.x;
	delta_dist = vector(1 / ray_dir.x, 1 / ray_dir.y);
	side_dist = get_side_dist(ray_dir, cell, delta_dist, game);
	while (!game->map.data[cell])
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			cell += -2 * (ray_dir.x < 0) + 1;
		}
		else
		{
			side_dist.y += delta_dist.y;
			cell += -2 * game->map.width * (ray_dir.x < 0) + game->map.width;
		}
	}
	if (side_dist.x < side_dist.y)
		return (side_dist.x - delta_dist.x);
	return (side_dist.y - delta_dist.y);
}
