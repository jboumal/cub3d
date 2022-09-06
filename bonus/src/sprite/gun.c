/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/06 21:56:05 by bperraud         ###   ########.fr       */
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
	printf("machinegun taken\n");
}

void	init_gun(t_game *game)
{
	t_sprite	*gun;
	int			i;

	i = 0;
	while (i <= 3)
	{
		gun = x_malloc(sizeof(t_sprite));
		gun->dist_to_p = 0;
		gun->angle = 0;
		gun->x_end = 0;
		gun->y_end = 0;
		if (i == 0)
		{
			load_texture(game->mlx, "img/sprite/gun/pistol.xpm", &gun->t);
			game->list_active_gun[0] = gun;
		}
		else if (i == 1)
			load_texture(game->mlx, "img/sprite/gun/mach.xpm", &gun->t);
		else if (i == 2)
			load_texture(game->mlx, "img/sprite/gun/gatling.xpm", &gun->t);
		else if (i == 3)
			load_texture(game->mlx, "img/sprite/gun/knife.xpm", &gun->t);
		bound_start(gun, gun->t);
		game->list_gun[i] = gun;
		i++;
	}
}

void	render_gun(t_game *game)
{
	t_sprite	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		gun->ceil = game->img_h / 6.0;
		gun->height = game->img_h - gun->ceil;
		gun->width = gun->height;
		gun->pixel_size = (int) gun->height / gun->t.height;
		if (gun->image == gun->t.n_image)
			gun->image = 0;
		else
		{
			if (gun->image)
				gun->image += 1;
			draw_sprite(game, gun, &gun->t, gun->image);
		}
	}
}
