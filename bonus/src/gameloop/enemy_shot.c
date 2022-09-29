/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_shot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:46 by jboumal           #+#    #+#             */
/*   Updated: 2022/09/29 21:50:48 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ennemy_shot(t_game *g, t_enemy *enemy)
{
	enemy->state = SHOOT;
	g->player_hp -= 3;
	printf("I have %d HP\n", g->player_hp);
	if (g->player_hp <= 0)
		quit(g);
}
