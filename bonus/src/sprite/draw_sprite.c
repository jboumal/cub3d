/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:48:56 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/26 17:35:15 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_big_pixel(t_game *g, t_sprite *s, int color, int ly)
{
	int		i;
	int		j;
	t_img	*img;

	img = &g->small_buffer;
	i = 0;
	while (i < s->pixel_size)
	{
		j = 0;
		while (j < s->pixel_size)
		{
			if (s->col + i <= g->img_w && s->ceil + ly + j <= g->img_h
				&& g->depth_buf[s->col + i] >= s->dist_player)
				my_mlx_pixel_put(img, s->col + i, s->ceil + ly + j, color);
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_game *g, t_sprite *s, t_img *t, int n_image)
{
	int		color;
	int		lx;
	int		ly;

	lx = s->width * s->x_end;
	while (lx < s->height)
	{
		ly = s->height * s->y_end;
		while (ly < s->height)
		{
			color = mlx_get_pixel(t, (lx + n_image * s->width) / s->width
					* (t->width / t->n_image), ly / s->height * t->height);
			if (color != NOT_PIXEL && color != STILL_NOT_PIXEL)
			{
				s->col = (0.5 * (s->angle / (g->player.fov / 2.0)) + 0.5)
					* g->img_w + lx - (s->width / 2.0);
				if (s->col >= 0 && s->ceil + ly >= 0)
					put_big_pixel(g, s, color, ly);
			}
			ly += s->pixel_size;
		}
		lx += s->pixel_size;
	}
}
