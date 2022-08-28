/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:25:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/28 18:52:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_game *g, t_sprite *obj, int i)
{
	t_sprite	*sprite;
	int			j;

	while (i >= 1 && obj->dist_to_p > g->list_sprite[i - 1]->dist_to_p)
	{
		sprite = g->list_sprite[i];
		g->list_sprite[i] = g->list_sprite[i - 1];
		g->list_sprite[i - 1] = sprite;
		i--;
	}
}
