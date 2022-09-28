/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:21:53 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 17:04:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_enemy(t_game *game, t_enemy *enemy)
{
	int	i;

	i = 0;
	while (game->list_sprite[i])
		i++;
	game->list_sprite[i] = &enemy->s;
	game->list_enemy[0] = enemy;
}

void	init_enemy_texture(t_game *game)
{
	t_enemy		*enemy;
	int			i;

	i = 0;
	enemy = x_malloc(sizeof(t_enemy));
	enemy->s.is_collect = 0;
	enemy->s.collect_action = NULL;
	enemy->s.x = 27.5;
	enemy->s.y = 9.5;
	enemy->s.t = get_img_from_xpm(game->mlx, "img/enemy/enemy1.xpm");
	bound_start(&enemy->s, enemy->s.t);
	enemy->s.image = 3;
	add_enemy(game, enemy);
}
