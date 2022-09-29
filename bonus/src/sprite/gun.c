/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/29 16:42:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collect_ammo(t_game *game, t_sprite *ammo)
{
	t_gun		*gun;

	(void) ammo;
	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		if (gun->is_knife)
		{
			game->list_active_gun[0] = game->list_gun[PISTOL];
			game->list_active_gun[0]->ammo = 8;
		}
		gun->ammo += 8;
	}
}

void	anim_gun(t_game *game)
{
	int			i;
	t_gun		*gun;

	i = 0;
	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		if (gun->ammo || gun->is_knife)
		{
			if (gun->is_knife)
				play_sound("weapons/knife/knife_slash1.wav");
			gun->ammo--;
			if (!gun->image)
				gun->image += 1;
		}
		else
		{
			if (game->list_active_gun[!game->active_gun]
				&& game->list_active_gun[!game->active_gun]->ammo)
				game->active_gun = !game->active_gun;
			else
				game->list_active_gun[0] = game->list_gun[KNIFE];
		}
	}
}

void	switch_gun(t_game *game)
{
	if (game->list_active_gun[1]
		&& game->list_active_gun[!game->active_gun]->ammo)
		game->active_gun = !game->active_gun;
}

void	replace_gun(t_game *game, t_sprite *gun)
{
	t_gun	*new_gun;

	new_gun = game->list_gun[gun->enum_gun];
	new_gun->ammo = 15;
	if (game->list_active_gun[0]->is_knife)
	{
		game->list_active_gun[0] = new_gun;
		game->list_active_gun[1] = NULL;
		return ;
	}
	if (!game->list_active_gun[1])
		game->list_active_gun[1] = new_gun;
	else
	{
		free(game->list_active_gun[game->active_gun]);
		game->list_active_gun[game->active_gun] = new_gun;
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
