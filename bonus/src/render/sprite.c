/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/23 13:32:35 by bel-mous         ###   ########.fr       */
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
		obj->is_in_fov = fabs(obj->angle) < g->player.fov / 2.0
			&& obj->dist_to_p >= 1.0;
		if (i != 0 && obj->is_in_fov)
			sort_sprite(g, obj, i);
	}
}

void	init_sprite(t_game *game)
{
	t_sprite	*obj;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	obj = malloc(sizeof(t_sprite));
	obj->x = 3.5;
	obj->y = 7.5;
	obj->size = 0.5;
	game->list_sprite[0] = obj;
	load_texture(game->mlx, "img/sprite/tree.xpm", &game->list_sprite[0]->t);
	obj = malloc(sizeof(t_sprite));
	obj->x = 6.5;
	obj->y = 12.5;
	obj->size = 0.4;
	game->list_sprite[1] = obj;
	load_texture(game->mlx, "img/sprite/armor.xpm", &game->list_sprite[1]->t);
	obj = malloc(sizeof(t_sprite));
	obj->x = 2.5;
	obj->y = 6.5;
	obj->size = 0.4;
	game->list_sprite[2] = obj;
	load_texture(game->mlx, "img/sprite/tree.xpm", &game->list_sprite[2]->t);
}

static void	draw_sprite(t_game *game, void *img, t_sprite obj)
{
	int		color;
	int		n_sprite_col;
	int		lx;
	int		ly;

	obj.ceil = ((SCREEN_H / 2.0) - (SCREEN_H / (obj.dist_to_p / obj.size)));
	obj.height = SCREEN_H - 2.0 * obj.ceil;
	obj.width = obj.height / (obj.t.height / obj.t.width);
	lx = 0;
	while (lx++ < obj.width)
	{
		ly = 0;
		while (ly++ < obj.height)
		{
			color = mlx_get_pixel(&obj.t.data, lx / obj.width * obj.t.width,
					ly / obj.height * obj.t.height);
			n_sprite_col = ((0.5 * (obj.angle / (game->player.fov / 2.0)) + 0.5)
					* SCREEN_W + lx - (obj.width / 2.0));
			if (n_sprite_col >= 0 && n_sprite_col < SCREEN_W)
			{
				if (color > 0 && game->depth_buf[n_sprite_col] >= obj.dist_to_p)
					my_mlx_pixel_put(img, n_sprite_col, obj.ceil + ly, color);
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
