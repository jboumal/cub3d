/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:36:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/29 09:59:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# define WALK_START 0
# define WALK_END 3
# define SHOOT_START 4
# define SHOOT_END 6
# define DIE_START 7
# define DIE_END 10

#include "cub3d.h"

void    init_enemy_texture(t_game *game);

enum e_enemy
{
	WALK,
	SHOOT,
	DIE
};

typedef struct s_enemy
{
	t_sprite		s;
	enum e_enemy	state;
}	t_enemy;

#endif