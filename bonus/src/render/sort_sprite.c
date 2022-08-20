/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:25:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/20 15:41:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_sprite(t_game *g, int i, int j)
{
	t_sprite	*sprite;

	sprite = g->list_sprite[i];
	g->list_sprite[i] = g->list_sprite[j];
	g->list_sprite[j] = sprite;
}

void	sort_sprite(t_game *g, t_sprite *obj, int i)
{
	int		j;

	if (obj->is_in_fov)
	{
		j = 0;
		while (i >= 1 && obj->dist_to_p > g->list_sprite[i - 1]->dist_to_p)
		{
			swap_sprite(g, i, i - 1);
			i--;
		}
	}
}
