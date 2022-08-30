/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:48:56 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/31 01:26:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprite(t_game *g, t_sprite *s, int i)
{
	t_sprite	*sprite;
	int			j;

	while (i >= 1 && s->dist_to_p > g->list_sprite[i - 1]->dist_to_p)
	{
		sprite = g->list_sprite[i];
		g->list_sprite[i] = g->list_sprite[i - 1];
		g->list_sprite[i - 1] = sprite;
		i--;
	}
}

void	compute_field_sprite(t_game *g)
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
		s->dist_to_p = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);
		s->angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		if (s->angle < -M_PI)
			s->angle += 2.0 * M_PI;
		if (s->angle > M_PI)
			s->angle -= 2.0 * M_PI;
		s->is_in_fov = fabs(s->angle) < (g->player.fov / 2.0);
		if (i != 0)
			sort_sprite(g, s, i);
	}
}

static void	put_big_pixel(t_game *g, t_sprite *s, int color, int ly)
{
	int		i;
	int		j;
	t_data	*img;

	img = &g->small_buffer;
	i = 0;
	while (i < s->pixel_size)
	{
		j = 0;
		while (j < s->pixel_size)
		{
			if (g->depth_buf[s->col + i] > s->dist_to_p)
				my_mlx_pixel_put(img, s->col + i, s->ceil + ly + j, color);
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_game *g, void *img, t_sprite *s)
{
	int		color;
	int		lx;
	int		ly;

	lx = s->width * s->x_start;
	while (lx <= s->width)
	{
		ly = s->height * s->y_start;
		while (ly <= s->height)
		{
			color = mlx_get_pixel(&s->t.data, lx / s->width * s->t.width,
					ly / s->height * s->t.height);
			if (color != NOT_PIXEL)
			{
				//col change trop quand l'angle augmente
				s->col = (0.5 * (s->angle / (g->player.fov / 2.0)) + 0.5)
					* (double) g->img_w + (double) lx - (s->width / 2.0);
				if (s->col >= 0 && s->col <= g->img_w && s->ceil + ly >= 0
					&& s->ceil + ly <= g->img_h)
					put_big_pixel(g, s, color, ly);
			}
			ly += s->pixel_size;
		}
		lx += s->pixel_size;
	}
}