/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/12 19:25:42 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anim_gun(t_game *game)
{
	int			i;
	t_gun		*gun;

	i = 0;
	gun = game->player.list_active_gun[game->player.active_gun];
	if (!gun->image)
		gun->image += 1;
}

void	switch_gun(t_game *game)
{
	if (game->player.list_active_gun[1])
		game->player.active_gun = !game->player.active_gun;
}

void	replace_gun(t_game *game, t_object *obj)
{
	if (!game->player.list_active_gun[1])
		game->player.list_active_gun[1] = game->list_gun[obj->enum_gun];
	else
	{
		free(game->player.list_active_gun[game->player.active_gun]);
		game->player.list_active_gun[game->player.active_gun] = game->list_gun[obj->enum_gun];
	}
}

void	init_gun(t_game *game)
{
	t_gun		*gun;
	int			i;

	i = 0;
	while (i < GUN_MAX)
	{
		gun = x_malloc(sizeof(t_gun));
		gun->s.dist_player = 0;
		gun->s.angle = 0;
		gun->s.x_end = 0;
		gun->s.y_end = 0;
		gun->image = 0;
		if (i == 0)
			load_texture(game->mlx, "img/sprite/gun/pistol.xpm", &gun->s.t);
		else if (i == 1)
			load_texture(game->mlx, "img/sprite/gun/mach.xpm", &gun->s.t);
		else if (i == 2)
			load_texture(game->mlx, "img/sprite/gun/gatling.xpm", &gun->s.t);
		else if (i == 3)
			load_texture(game->mlx, "img/sprite/gun/knife.xpm", &gun->s.t);
		bound_start(&gun->s, gun->s.t);
		game->list_gun[i] = gun;
		i++;
	}
	game->player.list_active_gun[0] = game->list_gun[0];
}

void	render_gun(t_game *game)
{
	t_gun	*gun;

	gun = game->player.list_active_gun[game->player.active_gun];
	if (gun)
	{
		gun->s.height = (game->img_h / gun->s.t.height - 1) * gun->s.t.height;
		gun->s.ceil = game->img_h - gun->s.height;
		gun->s.width = gun->s.height;
		gun->s.pixel_size = (int) gun->s.height / gun->s.t.height;
		if (gun->image == gun->s.t.n_image)
			gun->image = 0;
		else
		{
			draw_sprite(game, &gun->s, &gun->s.t, gun->image);
			if (gun->image)
				gun->image += 0.5;
		}
	}
}
