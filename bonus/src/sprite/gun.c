/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/03 16:00:11 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_gun(void *img, t_game *game)
{
	t_sprite	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		gun->ceil = game->img_h / 6.0;
		gun->height = game->img_h - gun->ceil;
		gun->width = gun->height / (gun->t.height / gun->t.width);
		gun->pixel_size = (int) gun->height / gun->t.height;
		draw_sprite(game, img, gun, &gun->t);
	}
}
