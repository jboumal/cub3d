/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:38 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 17:00:52 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Temporary function to be deleted when parsing works.
void	temp_init_map(t_game *game)
{
	static int	map[49] = {
		1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1,
	};

	game->map.data = map;
	game->map.width = 7;
	game->map.height = 7;
	game->player.pos.x = 2.6;
	game->player.pos.y = 3.4;
}

void	parser(t_game *game, char **argv)
{
	(void) argv;
	temp_init_map(game);
}
