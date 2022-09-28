/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:27:35 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 17:46:19 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_gun(t_game *game, t_gun *gun, int i)
{
	gun->s.dist_to_p = 0;
	gun->s.angle = 0;
	gun->s.image = 0;
	if (i == PISTOL)
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/pistol.xpm");
	else if (i == MACH)
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/mach.xpm");
	else if (i == GATLING)
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/gatling.xpm");
	else if (i == KNIFE)
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/knife.xpm");
	bound_start(&gun->s, gun->s.t);
	gun->s.height = (game->img_h / gun->s.t.height - 1) * gun->s.t.height;
	gun->s.ceil = game->img_h - gun->s.height;
	gun->s.width = gun->s.height;
	gun->s.pixel_size = (int) gun->s.height / gun->s.t.height;
}

void	init_gun(t_game *game)
{
	t_gun		*gun;
	int			i;

	i = 0;
	while (i < GUN_MAX)
	{
		gun = x_malloc(sizeof(t_gun));
		init_sprite_gun(game, gun, i);
		gun->image = 0;
		gun->ammo = 15;
		gun->is_knife = i == KNIFE;
		game->list_gun[i] = gun;
		i++;
	}
	game->list_active_gun[0] = game->list_gun[0];
}
