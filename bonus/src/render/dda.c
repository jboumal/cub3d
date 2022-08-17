/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:01:48 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 15:55:34 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	get_side_dist(t_vector delta_dist, t_ray *ray, t_game *g)
{
	t_vector	pos;
	t_vector	side_dist;

	pos = g->player.pos;
	if (ray->dir.x < 0)
		side_dist.x = (pos.x - ray->cell % g->map.width) * delta_dist.x;
	else
		side_dist.x = (ray->cell % g->map.width + 1.0 - pos.x) * delta_dist.x;
	if (ray->dir.y < 0)
		side_dist.y = (pos.y - ray->cell / g->map.width) * delta_dist.y;
	else
		side_dist.y = (ray->cell / g->map.width + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}

static t_vector	compute_cell(
	t_ray *ray,
	t_vector delta_dist,
	t_vector side_dist,
	t_game *g)
{
	if (side_dist.x < side_dist.y)
	{
		side_dist.x += delta_dist.x;
		ray->cell += -2 * (ray->dir.x < 0) + 1;
		ray->side = W * (ray->dir.x <= 0) + E * (ray->dir.x > 0);
		if (g->map.data[ray->cell] == 2)
		{
			ray->door_side = ray->side;
			ray->door_dist = side_dist.x - delta_dist.x + delta_dist.x / 2;
		}
	}
	else
	{
		side_dist.y += delta_dist.y;
		ray->cell += -2 * g->map.width * (ray->dir.y < 0) + g->map.width;
		ray->side = N * (ray->dir.y >= 0) + S * (ray->dir.y < 0);
		if (g->map.data[ray->cell] == 2)
		{
			ray->door_side = ray->side;
			ray->door_dist = side_dist.y - delta_dist.y + delta_dist.y / 2;
		}
	}
	return (side_dist);
}

void	dda(t_ray *ray, t_game *g)
{
	t_vector	delta_dist;
	t_vector	side_dist;

	ray->cell = (int)g->player.pos.y * g->map.width + (int)g->player.pos.x;
	delta_dist = vector(1 / fabs(ray->dir.x), 1 / fabs(ray->dir.y));
	side_dist = get_side_dist(delta_dist, ray, g);
	ray->door_dist = 0;
	while (!g->map.data[ray->cell] || g->map.data[ray->cell] == 2)
		side_dist = compute_cell(ray, delta_dist, side_dist, g);
	ray->wall_dist = side_dist.y - delta_dist.y;
	if (ray->side % 2)
		ray->wall_dist = side_dist.x - delta_dist.x;
}
