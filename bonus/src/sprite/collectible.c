/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:18:00 by bperraud          #+#    #+#             */
/*   Updated: 2022/10/04 14:59:02 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_gun(t_game *game, t_sprite *gun)
{
	t_gun	*new_gun;
	t_gun	*active_gun;

	active_gun = game->list_active_gun[game->active_gun];
	new_gun = game->list_gun[gun->take_gun];
	game->ammo += 8;
	if (active_gun->is_knife)
	{
		game->list_active_gun[0] = game->list_gun[PISTOL];
	}
	if (!game->list_active_gun[1])
		game->list_active_gun[1] = new_gun;
	else
	{
		free(game->list_active_gun[game->active_gun]);
		game->list_active_gun[game->active_gun] = new_gun;
	}
	game->active_gun = 1;
}

void	collect_key(t_game *game, t_sprite *key)
{
	t_door	*door;

	(void) key;
	door = get_door(LOCKED_DOOR, game);
	if (door)
	{
		door->is_locked = !door->is_locked;
	}
}

void	collect_chiken(t_game *game, t_sprite *chicken)
{
	(void) chicken;
	if (game->player_hp < 100)
	{
		play_sound("sounds/Interaction/items/pickup/health/hot_pickup.wav", game);
		game->player_hp += 10;
		if (game->player_hp > 100)
			game->player_hp = 100;
	}
}

void	collect_ammo(t_game *game, t_sprite *ammo)
{
	t_gun		*gun;

	(void) ammo;
	play_sound("sounds/ammo_pickup.wav", game);
	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		if (gun->is_knife)
		{
			game->list_active_gun[0] = game->list_gun[PISTOL];
		}
		game->ammo += 8;
	}
}
