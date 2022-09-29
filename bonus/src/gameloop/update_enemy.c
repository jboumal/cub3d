/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:57:03 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/29 10:28:33 by vrogiste         ###   ########.fr       */
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
	if (vector_norme(v) > 3)
	{
		enemy->state = WALK;
		np = vector(enemy->s.x + dir.x * (MOVE_SPEED * 3), enemy->s.y + dir.y * (MOVE_SPEED * 3));
		g->map.object_map[(int)enemy->s.y * g->map.width + (int)enemy->s.x] = 0;
		if (!g->map.data[(int)enemy->s.y * g->map.width + (int)np.x]
			|| can_pass_door((int)enemy->s.y * g->map.width + (int)np.x, g))
			enemy->s.x = np.x;
		if (!g->map.data[(int)np.y * g->map.width + (int)enemy->s.x]
			|| can_pass_door((int)np.y * g->map.width + (int)enemy->s.x, g))
			enemy->s.y = np.y;
		g->map.object_map[(int)np.y * g->map.width + (int)enemy->s.x] = 1;
	}
	else
		enemy->state = SHOOT;
}

static int start(t_enemy *enemy)
{
	if (enemy->state == WALK)
		return (WALK_START);
	else if (enemy->state == SHOOT)
		return (SHOOT_START);
	else if (enemy->state == SHOT)
		return (SHOT_START);
	else
		return (DIE_START);
}

static int end(t_enemy *enemy)
{
	if (enemy->state == WALK)
		return (WALK_END);
	else if (enemy->state == SHOOT)
		return (SHOOT_END);
	else if (enemy->state == SHOT)
		return (SHOT_END);
	else
		return (DIE_END);
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
				if (enemy->hp <= 0)
					enemy->state = DIE;
				else if (g->state.shoot)
				{
					enemy->state = SHOT;
					enemy->hp -= 20;
				}
				else
					update_enemy_pos(g, enemy);
				if (enemy->s.image < start(enemy))
					enemy->s.image = start(enemy);
				if (enemy->s.image != DIE_END)
					enemy->s.image += 1;
				if (enemy->s.image > end(enemy))
					enemy->s.image = start(enemy);
			}
			i++;
		}
		g->state.shoot = 0;
	}
	accu++;
}