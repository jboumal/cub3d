/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:17:38 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 22:00:14 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_rect(t_rect *rect, int size)
{
	rect->x = 0;
	rect->y = 0;
	rect->width = size;
	rect->height = size;
	rect->color = 0;
}

static int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			my_mlx_pixel_put(img, j, i, rect.color);
			j++;
		}
		i++;
	}
	return (0);
}

static void	drawline(t_img *img, t_vector p0, t_vector p1, t_game *g)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = p1.x - p0.x;
	delta_y = p1.y - p0.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = p0.x;
	pixel_y = p0.y;
	while (pixels)
	{
		if (
			pixel_x >= 0 && pixel_y >= 0
			&& pixel_x < g->map.width * TILEMAP_SIZE
			&& pixel_y < g->map.height * TILEMAP_SIZE)
			my_mlx_pixel_put(img, pixel_x, pixel_y, 0xff0000);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

static void	render_miniplayer(t_img *img, t_game *g)
{
	t_rect		rect;
	t_vector	position0;
	t_vector	position1;
	t_vector	position2;
	t_player	p;

	p = g->player;
	init_rect(&rect, 6);
	rect.x = g->player.pos.x * TILEMAP_SIZE - 6 / 2;
	rect.y = (g->map.height - g->player.pos.y) * TILEMAP_SIZE - 6 / 2;
	rect.color = 0xFF0000;
	position0 = vector(rect.x + 3, rect.y + 3);
	position1 = vector((p.pos.x + (p.dir.x * 1 - p.plane.x) * 2) * TILEMAP_SIZE,
			((g->map.height - p.pos.y) - (p.dir.y - p.plane.y) * 2)
			* TILEMAP_SIZE);
	position2 = vector((p.pos.x + (p.dir.x * 1 + p.plane.x) * 2) * TILEMAP_SIZE,
			((g->map.height - p.pos.y) - (p.dir.y + p.plane.y) * 2)
			* TILEMAP_SIZE);
	drawline(img, position0, position1, g);
	drawline(img, position0, position2, g);
	drawline(img, position1, position2, g);
	render_rect(img, rect);
}

void	render_minimap(t_img *img, t_game *game)
{
	int		i;
	t_rect	rect;
	t_map	map;

	init_rect(&rect, TILEMAP_SIZE);
	map = game->map;
	i = 0;
	while (i < map.height * map.width)
	{
		rect.x = (i % map.width) * TILEMAP_SIZE;
		rect.y = ((map.height * map.width - 1 - i) / map.width) * TILEMAP_SIZE;
		if (map.data[i] == 1)
			rect.color = 0x4B7A68;
		else if (map.data[i] == 0)
			rect.color = 0x7CE7D6;
		else
			rect.color = 0;
		render_rect(img, rect);
		i++;
	}
	render_miniplayer(img, game);
}
