/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/19 23:53:44 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps_counter(void)
{
	static int		n_frame = 0;
	static int		second = 0;
	struct timeval	t;

	n_frame ++;
	gettimeofday(&t, NULL);
	if (t.tv_sec > second)
	{
		printf ("%d fps\n", n_frame);
		n_frame = 0;
		second = t.tv_sec;
	}
}

static void	update_door(t_game *g)
{
	if (!g->state.door_opened && g->state.door_ratio < 1)
		g->state.door_ratio += 0.01;
	if (g->state.door_opened && g->state.door_ratio > 0)
		g->state.door_ratio -= 0.01;
}

static void	game_update(t_game *game)
{
	translate_cam(game);
	rotate_cam(game);
	update_door(game);
}

int	game_loop(t_game *game)
{
	fps_counter();
	if (LINUX)
		my_mouse_hook(game);
	game_update(game);
	render(game);
	return (0);
}
