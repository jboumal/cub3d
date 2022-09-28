/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:57:03 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/28 17:56:05 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void update_enemy_pos(t_game *g, t_enemy *enemy)
{
	t_vector	v;
	t_vector	dir;
	t_vector	np;

	v = vector(g->player.pos.x - enemy->s.x, g->player.pos.y - enemy->s.y);
	dir = vector_normalize(v);
	if (vector_norme(v) > 2)
	{
		np = vector(enemy->s.x + dir.x * (MOVE_SPEED/1000), enemy->s.y + dir.y * (MOVE_SPEED/1000));
		if (!g->map.data[(int)np.y * g->map.width + (int)np.x])
			enemy->s.x = np.x;
		if (!g->map.data[(int)np.y * g->map.width + (int)np.x])
			enemy->s.y = np.y;
	}
}

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
				update_enemy_pos(g, enemy);
			}
			i++;
		}
	}
	accu++;
}
