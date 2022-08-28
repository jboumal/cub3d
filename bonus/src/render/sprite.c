/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/28 00:12:25 by bperraud         ###   ########.fr       */
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
	while (i++ < 9)
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
		obj->is_in_fov = (fabs(obj->angle) < g->player.fov / 2.0
				&& obj->dist_to_p >= 1.0);
		if (i != 0 && obj->is_in_fov)
			sort_sprite(g, obj, i);
	}
}

static void	draw_sprite(t_game *g, void *img, t_sprite s)
{
	int		color;
	int		col;
	int		lx;
	int		ly;

	s.ceil = ((SCREEN_H / 2.0) - (SCREEN_H / (s.dist_to_p / s.size)));
	s.height = (SCREEN_H - 2.0 * s.ceil);
	s.width = s.height / (s.t.height / s.t.width);
	lx = 0;
	while (lx++ < s.width)
	{
		ly = 0;
		while (ly++ < s.height)
		{
			color = mlx_get_pixel(&s.t.data, lx / s.width * s.t.width,
					ly / s.height * s.t.height);
			if (color > 0)
			{
				col = (0.5 * (s.angle / (g->player.fov / 2) + 1))
					* SCREEN_W + lx - (s.width / 2);
				if (col >= 0 && col < SCREEN_W && s.ceil + ly >= 0 && s.ceil
					+ ly < SCREEN_H && g->depth_buf[col] >= s.dist_to_p)
					my_mlx_pixel_put(img, col, s.ceil + ly, color);
			}
		}
	}
}

void	render_sprites(void	*img, t_game *g)
{
	t_sprite	*obj;
	int			i;

	compute_field_sprite(g);
	i = -1;
	while (i++ < 9)
	{
		obj = g->list_sprite[i];
		if (obj && obj->is_in_fov)
			draw_sprite(g, img, *obj);
	}
}
