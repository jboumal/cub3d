/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:21:53 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 15:16:24 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_enemy_texture(t_game *game)
{
    t_sprite	*enemy;

	enemy = x_malloc(sizeof(t_sprite));
    enemy->is_collect = 0;
	enemy->collect_action = NULL;
	enemy->x = 27.5;
    enemy->y = 9.5;
	enemy->t = get_img_from_xpm(game->mlx, "img/enemy/enemy1.xpm");
	bound_start(enemy, enemy->t);
    enemy->image = 3;
	game->list_sprite[3] = enemy;
}