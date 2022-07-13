/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:01:48 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/13 13:20:31 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dda(t_vector ray_dir, t_game *game)
{
	int			cell;
	t_vector	delta_dist;
	t_vector	side_dist;
	int			step;

	cell = (int)game->player.pos.y * game->map.width + (int)game->player.pos.x;
	delta_dist = vector(1 / ray_dir.x, 1 / ray_dir.y);
}
