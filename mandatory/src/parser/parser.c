/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:38 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 14:17:35 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Temporary function to be deleted when parsing works.
void	temp_init_map(t_game *game)
{
	static int	map[] = {
		1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1,
	};

	game->map.data = map;
	game->map.width = 7;
	game->map.height = 7;
	game->player.pos.x = 2;
	game->player.pos.y = 2.3;
	game->player.dir.x = 0;
	game->player.dir.y = 1;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0;
}

void	parser(int argc, char **argv, t_game *game)
{
	(void) argc;
	(void) argv;
	temp_init_map(game);
}
