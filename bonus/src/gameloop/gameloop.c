/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/17 16:06:35 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps_counter(t_game *g)
{
	static int		n_frame = 0;
	static int		second = 0;
	struct timeval	t;

	n_frame++;
	gettimeofday(&t, NULL);
	if (t.tv_sec > second)
	{
		g->fps = n_frame;
		n_frame = 0;
		second = t.tv_sec;
	}
}

int	game_loop(t_game *game)
{

	fps_counter(game);
	if (LINUX)
		my_mouse_hook(game);
	if (game->scene == TITLE)
	 	title_update(game);
	else {
		game_update(game);
		render(game);
	}
	return (0);
}
