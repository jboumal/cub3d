/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:57:03 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/28 16:30:06 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_enemy(t_game *g)
{
	static int	accu;
	int			i;
	t_enemy *enemy;

	if (!(accu % 10))
	{
		i = 0;
		while (i < ENEMY_MAX)
		{
			if (g->list_enemy[i])
			{
				enemy = g->list_enemy[i];
				enemy->s.image++;
				enemy->s.image = (int)enemy->s.image % (enemy->s.t.width / enemy->s.t.height);
			}
			i++;
		}
	}
	accu++;
}
