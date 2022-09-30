/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:36:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/30 16:28:34 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# define WALK_START 0
# define WALK_END 3
# define SHOOT_START 4
# define SHOOT_END 6
# define SHOT_START 7
# define SHOT_END 7
# define DIE_START 8
# define DIE_END 10
# define REACH_KNIFE 1.3

# include "cub3d.h"

void	create_enemy(t_game *game, double x, double y, char *path);

enum e_enemy
{
	WALK,
	SHOOT,
	SHOT,
	DIE
};

typedef struct s_enemy
{
	t_sprite		s;
	enum e_enemy	state;
	int				hp;
}	t_enemy;

#endif
