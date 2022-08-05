/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:54:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/05 11:54:35 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_error(char *msg)
{
	dputstr(STDERR_FILENO, "Error\n");
	dputstr(STDERR_FILENO, msg);
	dputstr(STDERR_FILENO, "\n");
	exit(EXIT_FAILURE);
}

enum e_side	get_direction(char c)
{
	return ((c == 'N') * N + (c == 'S') * S + (c == 'W') * W + (c == 'E') * E);
}

void	parse(int argc, char **argv, t_game *game)
{
	int		fd;
	char	*map_str;

	if (argc != 2)
		parsing_error("invalid number of arguments");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	parse_textures(game, fd);
	map_str = get_map_str(fd);
	parse_map(map_str, game);
	check_map(game);
	free(map_str);
	close(fd);
}
