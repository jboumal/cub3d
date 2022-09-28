/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 16:27:53 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anim_gun(t_game *game)
{
	int			i;
	t_gun		*gun;

	i = 0;
	gun = game->list_active_gun[game->active_gun];
	if (!gun->image)
		gun->image += 1;
}

void	switch_gun(t_game *game)
{
	if (game->list_active_gun[1])
		game->active_gun = !game->active_gun;
}

void	replace_gun(t_game *game, t_sprite *gun)
{
	if (!game->list_active_gun[1])
		game->list_active_gun[1] = game->list_gun[gun->enum_gun];
	else
	{
		free(game->list_active_gun[game->active_gun]);
		game->list_active_gun[game->active_gun] = game->list_gun[gun->enum_gun];
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
