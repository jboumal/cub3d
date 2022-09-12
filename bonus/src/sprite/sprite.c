/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 00:12:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/07 20:25:05 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_sprite(t_game *g, t_sprite *s, int sprite_index)
{
	int	i;

	if (s->collect_action)
		s->collect_action(g, s);
	free(g->list_sprite[sprite_index]);
	g->list_sprite[sprite_index] = NULL;
	i = sprite_index;
	while (i < SPRITE_MAX - 1)
	{
		if (g->list_sprite[i + 1])
		{
			g->list_sprite[i] = g->list_sprite[i + 1];
			g->list_sprite[i + 1] = NULL;
		}
		i++;
	}
}

void	render_sprites(t_game *g)
{
	t_sprite	*s;
	int			sprite_index;

	compute_field_sprite(g);
	sprite_index = 0;
	while (sprite_index < SPRITE_MAX - 1)
	{
		s = g->list_sprite[sprite_index];
		if (s)
		{
			if (s->dist_to_p >= MIN_DIST && s->is_in_fov && g->map.visible_tiles
				[(int)((s->y - 0.5) * g->map.width + s->x - 0.5)])
			{
				s->ceil = g->img_h / 2.0 - (g->img_h / (s->dist_to_plane * 2.0));
				s->height = g->img_h - 2.0 * s->ceil;
				s->width = s->height / (s->t.height / s->t.width);
				s->pixel_size = (int) s->height / s->t.height;
				if (s->pixel_size < 1)
					s->pixel_size = 1;
				draw_sprite(g, s, &s->t, 0);
			}
			if (s->is_collect && s->dist_to_p <= MIN_DIST)
				remove_sprite(g, s, sprite_index);
		}
		sprite_index++;
	}
}
