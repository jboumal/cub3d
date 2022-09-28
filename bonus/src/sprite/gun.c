/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 14:26:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anim_gun(t_game *game)
{
	int			i;
	t_sprite	*gun;

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

void	init_gun(t_game *game)
{
	t_sprite	*gun;
	int			i;

	i = 0;
	while (i < GUN_MAX)
	{
		gun = x_malloc(sizeof(t_sprite));
		gun->dist_to_p = 0;
		gun->angle = 0;
		gun->image = 0;
		if (i == 0)
			gun->t = get_img_from_xpm(game->mlx, "img/sprite/gun/pistol.xpm");
		else if (i == 1)
			gun->t = get_img_from_xpm(game->mlx, "img/sprite/gun/mach.xpm");
		else if (i == 2)
			gun->t = get_img_from_xpm(game->mlx, "img/sprite/gun/gatling.xpm");
		else if (i == 3)
			gun->t = get_img_from_xpm(game->mlx, "img/sprite/gun/knife.xpm");
		bound_start(gun, gun->t);
		gun->height = (game->img_h / gun->t.height - 1) * gun->t.height;
		gun->ceil = game->img_h - gun->height;
		gun->width = gun->height;
		gun->pixel_size = (int) gun->height / gun->t.height;
		game->list_gun[i] = gun;
		i++;
	}
	game->list_active_gun[0] = game->list_gun[0];
}

void	render_gun(t_game *game)
{
	t_sprite	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		
		if (gun->image == gun->t.width / gun->t.height)
			gun->image = 0;
		else
		{
			draw_sprite(game, gun, &gun->t, gun->image);
			if (gun->image)
				gun->image += 0.5;
		}
	}
}
