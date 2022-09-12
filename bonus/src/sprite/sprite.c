/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 00:12:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/12 19:27:34 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remove_object(t_game *g, t_object *obj, int sprite_index)
{
	int	i;

	free(g->list_collect[sprite_index]);
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

void	collect_items(t_game *g)
{
	t_object	*obj;
	int			collect_index;

	collect_index = 0;
	while (collect_index < SPRITE_MAX - 1)
	{
		obj = g->list_collect[collect_index];
		if (obj)
		{
			if (hypot(obj->s.x - g->player.pos.x, obj->s.y - g->player.pos.y)
				<= MIN_DIST)
			{
				free(g->list_collect[collect_index]);
				g->list_collect[collect_index] = NULL;
				if (obj->collect_action)
					obj->collect_action(g, obj);
			}
		}
		collect_index++;
	}
}

static void	sort_sprite(t_game *g, t_sprite *s, int i)
{
	t_sprite	*sprite;

	while (i >= 1 && s->dist_player > g->list_sprite[i - 1]->dist_player)
	{
		sprite = g->list_sprite[i];
		g->list_sprite[i] = g->list_sprite[i - 1];
		g->list_sprite[i - 1] = sprite;
		i--;
	}
}

static void	compute_field_sprite(t_game *g)
{
	t_sprite	*s;
	double		fvec_x;
	double		fvec_y;
	int			i;

	i = -1;
	while (i++ < SPRITE_MAX - 1)
	{
		s = g->list_sprite[i];
		if (!s)
			continue ;
		fvec_x = s->x - g->player.pos.x;
		fvec_y = s->y - g->player.pos.y;
		s->dist_player = hypot(fvec_x, fvec_y);
		s->angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		s->dist_plane = g->player.dir.x * fvec_x + g->player.dir.y * fvec_y;
		if (s->angle < -M_PI)
			s->angle += 2.0 * M_PI;
		if (s->angle > M_PI)
			s->angle -= 2.0 * M_PI;
		s->is_in_fov = fabs(s->angle) - 0.09 < (g->player.fov / 2.0);
		if (i != 0)
			sort_sprite(g, s, i);
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
			if (s->dist_player >= MIN_DIST && s->is_in_fov && g->map.visible_tiles
				[(int)((s->y - 0.5) * g->map.width + s->x - 0.5)])
			{
				s->ceil = g->img_h / 2.0 - (g->img_h / (s->dist_plane * 2.0));
				s->height = g->img_h - 2.0 * s->ceil;
				s->width = s->height / (s->t.height / s->t.width);
				s->pixel_size = (int) s->height / s->t.height;
				if (s->pixel_size < 1)
					s->pixel_size = 1;
				draw_sprite(g, s, &s->t, 0);
			}
		}
		sprite_index++;
	}
}
