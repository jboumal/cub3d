/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:18:00 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/29 18:52:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_gun(t_game *game, t_sprite *gun)
{
	t_gun	*new_gun;

	new_gun = game->list_gun[gun->take_gun];
	new_gun->ammo = 8;
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

void	collect_chiken(t_game *game, t_sprite *chicken)
{
	(void) game;
	(void) chicken;
	play_sound("Interaction/items/pickup/health/hot_pickup.wav");
}

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
