/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:27:35 by bperraud          #+#    #+#             */
/*   Updated: 2022/10/04 15:11:00 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_gun(t_game *game, t_gun *gun, int i)
{
	if (i == PISTOL)
	{
		gun->path_sound = "sounds/weapons/colt/coltf1.wav";
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/pistol.xpm");
		gun->dmg = 20;
	}
	else if (i == MACH)
	{
		gun->path_sound = "sounds/weapons/thompson/thompson.wav";
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/mach.xpm");
		gun->dmg = 25;
	}
	else if (i == GATLING)
	{
		gun->path_sound = "sounds/weapons/thompson.wav";
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/gatling.xpm");
		gun->dmg = 30;
	}
	else if (i == KNIFE)
	{
		gun->path_sound = "sounds/weapons/knife/knife_slash1.wav";
		gun->s.t = get_img_from_xpm(game->mlx, "img/sprite/gun/knife.xpm");
		gun->dmg = 10;
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
		init_sprite_gun(game, gun, i);
		gun->image = 0;
		gun->is_knife = i == KNIFE;
		game->ammo = 8;
		gun->s.dist_to_p = 0;
		gun->s.angle = 0;
		gun->s.image = 0;
		gun->s.height = (game->img_h / gun->s.t.height - 1) * gun->s.t.height;
		gun->s.ceil = game->img_h - gun->s.height;
		gun->s.width = gun->s.height;
		gun->s.pixel_size = (int) gun->s.height / gun->s.t.height;
		bound_start(&gun->s, gun->s.t);
		game->list_gun[i] = gun;
		i++;
	}
	game->list_active_gun[0] = game->list_gun[0];
}
