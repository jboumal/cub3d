/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/12 18:25:13 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_update(t_game *game)
{
	(void) game;
}

int	game_loop(t_game *game)
{
	float	delta_time;

	delta_time = 10000 / FPS;
	if (game->accumulator >= delta_time)
	{
		game_update(game);
		render(game);
		game->accumulator -= delta_time;
	}
	game->accumulator++;
	return (0);
}
