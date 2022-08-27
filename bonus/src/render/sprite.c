/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/27 18:03:01 by bperraud         ###   ########.fr       */
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

static void	draw_sprite(t_game *game, void *img, t_sprite obj)
{
	int		color;
	int		n_sprite_col;
	int		lx;
	int		ly;

	obj.ceil = ((SCREEN_H / 2.0) - (SCREEN_H / (obj.dist_to_p / obj.size)));
	obj.height = (SCREEN_H - 2.0 * obj.ceil);
	obj.width = obj.height / (obj.t.height / obj.t.width);
	lx = 0;
	while (lx++ < obj.width)
	{
		ly = 0;
		while (ly++ < obj.height)
		{
			color = mlx_get_pixel(&obj.t.data, lx / obj.width * obj.t.width,
					ly / obj.height * obj.t.height);
			if (color > 0)
			{
				n_sprite_col = ((0.5 * (obj.angle / (game->player.fov / 2.0)) + 0.5)
						* SCREEN_W + lx - (obj.width / 2.0));
				if (n_sprite_col >= 0 && n_sprite_col < SCREEN_W)
				{
					n_sprite_col = ((0.5 * (obj.angle / (game->player.fov / 2.0)) + 0.5)
							* SCREEN_W + lx - (obj.width / 2.0));
					if (n_sprite_col >= 0 && n_sprite_col < SCREEN_W && obj.ceil + ly
						>= 0 && obj.ceil + ly < SCREEN_H
						&& game->depth_buf[n_sprite_col] >= obj.dist_to_p)
						my_mlx_pixel_put(img, n_sprite_col, obj.ceil + ly, color);
				}
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
