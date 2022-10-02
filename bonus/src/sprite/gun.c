/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/10/02 23:07:40 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anim_gun(t_game *game)
{
	t_gun		*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		if (game->ammo || gun->is_knife)
		{
			play_sound(gun->path_sound, game);
			if (!gun->is_knife)
				game->ammo--;
			if (!gun->image)
				gun->image += 1;
		}
		if (!game->ammo && !gun->is_knife)
		{
			game->list_active_gun[0] = game->list_gun[KNIFE];
			game->active_gun = 0;
		}
	}
}

void	switch_gun(t_game *game)
{
	if (game->list_active_gun[1]
		&& game->ammo)
	{
		play_sound("weapons/change.wav", game);
		game->active_gun = !game->active_gun;
	}
}

void	render_gun(t_game *game)
{
	t_gun	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		if (gun->image == gun->s.t.width / gun->s.t.height)
			gun->image = 0;
		else
		{
			draw_sprite(game, &gun->s, &gun->s.t, gun->image);
			if (gun->image)
				gun->image += 0.5;
		}
	}
}
