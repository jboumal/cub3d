/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:36:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/28 15:36:52 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

#include "cub3d.h"

void    init_enemy_texture(t_game *game);

typedef struct s_enemy
{
	t_sprite		s;
}	t_enemy;

#endif