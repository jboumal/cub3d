/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 00:12:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/29 16:17:54 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	compute_field_sprite(t_game *g)
{
	t_sprite	*obj;
	double		fvec_x;
	double		fvec_y;
	int			i;

	i = -1;
	while (i++ < SPRITE_MAX - 1)
	{
		obj = g->list_sprite[i];
		if (!obj)
			continue ;
		fvec_x = obj->x - g->player.pos.x;
		fvec_y = obj->y - g->player.pos.y;
		obj->dist_to_p = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);
		obj->angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		if (obj->angle < -M_PI)
			obj->angle += 2.0 * M_PI;
		if (obj->angle > M_PI)
			obj->angle -= 2.0 * M_PI;
		obj->is_in_fov = fabs(obj->angle) < g->player.fov / 2.0;
		if (i != 0)
			sort_sprite(g, obj, i);
	}
}

static void	draw_sprite(t_game *g, void *img, t_sprite *s)
{
	int		color;
	int		col;
	int		lx;
	int		ly;

	lx = s->width * s->x_start;
	while (lx++ < s->width)
	{
		ly = s->height * s->y_start;
		while (ly++ < s->height)
		{
			color = mlx_get_pixel(&s->t.data, lx / s->width * s->t.width,
					ly / s->height * s->t.height);
			if (color > 0 && color != NOT_PIXEL)
			{
				col = (0.5 * (s->angle / (g->player.fov / 2.0) + 1))
					* g->img_w + lx - (s->width / 2.0);
				if (col >= 0 && col < g->img_w && s->ceil + ly >= 0 && s->ceil
					+ ly < g->img_h && g->depth_buf[col] >= s->dist_to_p)
					my_mlx_pixel_put(img, col, s->ceil + ly, color);
			}
		}
	}
}

void	remove_sprite(t_game *g, int sprite_index)
{
	int	i;

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
			if (s->dist_to_p >= MIN_SPRITE_DIST)
			{
				s->ceil = (g->img_h / 2.0 - (g->img_h / (s->dist_to_p * 2.0)));
				s->height = g->img_h - 2.0 * s->ceil;
				s->width = s->height / (s->t.height / s->t.width);
				draw_sprite(g, img, s);
			}
			else if (s->is_collect)
				remove_sprite(g, sprite_index);
		}
		sprite_index++;
	}
}
