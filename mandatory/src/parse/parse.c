/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:38 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 22:02:54 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser(char **argv, t_game *game)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	parse_textures(game, fd);
	parse_map(get_map_str(fd), game);
	game->player.plane.x = 0.66;
	game->player.plane.y = 0;
}
