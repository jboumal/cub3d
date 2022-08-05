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

void	init_rect(t_rect *rect, int size)
{
	rect->x = 0;
	rect->y = 0;
	rect->width = size;
	rect->height = size;
	rect->color = 0;
}

int	render_rect(t_data *img, t_rect rect)
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

void	render_miniplayer(t_data *img, t_game *game)
{
	t_rect	rect;

	init_rect(&rect, 6);
	rect.x = game->player.pos.x * TILEMAP_SIZE - 6 / 2;
	rect.y = game->player.pos.y * TILEMAP_SIZE - 6 / 2;
	rect.color = 0xFF0000;
	render_rect(img, rect);
}

void	render_minimap(t_data *img, t_game *game)
{
	size_t	i;
	t_rect	rect;
	t_map	map;

	init_rect(&rect, TILEMAP_SIZE);
	map = game->map;
	i = 0;
	while (i < map.height * map.width)
	{
		rect.x = (i % map.width) * TILEMAP_SIZE;
		rect.y = (i / map.width) * TILEMAP_SIZE;
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
