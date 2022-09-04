/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 00:12:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/04 18:53:17 by bperraud         ###   ########.fr       */
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

void	render_sprites(void	*img, t_game *g)
{
	t_sprite	*s;
	int			sprite_index;

	compute_field_sprite(g);
	sprite_index = 0;
	while (sprite_index < SPRITE_MAX - 1)
	{
		s = g->list_sprite[sprite_index];
		if (s && s->is_in_fov)
		{
			if (s->dist_to_p >= MIN_DIST)
			{
				s->ceil = (g->img_h / 2.0 - (g->img_h / (s->dist_to_p * 2.0)));
				s->height = (g->img_h - 2.0 * s->ceil);
				s->width = s->height / (s->t.height / s->t.width);
				s->ceil += fabs(s->angle) * 12.0;
				s->pixel_size = (int) s->height / s->t.height;
				if (s->pixel_size < 1)
					s->pixel_size = 1;
				draw_sprite(g, img, s, &s->t);
			}
			else if (s->is_collect)
				remove_sprite(g, s, sprite_index);
		}
		sprite_index++;
	}
}
