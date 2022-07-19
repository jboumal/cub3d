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

// Temporary function to be deleted when parsing works.
void	temp_init_map(t_game *game)
{
	static int	map[49] = {
		1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1,
	};

	game->map.data = map;
	game->map.width = 7;
	game->map.height = 7;
	game->player.pos.x = 3;
	game->player.pos.y = 3;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
}

static char	*gnl_not_empty(int file_fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(file_fd);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\r')
	{
		free(line);
		return (gnl_not_empty(file_fd));
	}
	else
		return (line);
}

static int	parse_direction_and_color(t_game *game, int file_fd)
{
	char	*line;

	line = gnl_not_empty(file_fd);
	return (0);
}

static int	parse_map(t_game *game, int file_fd)
{
	return (0);
}


void	exit_error(char *str)
{
	write(2, "Error\n" , ft_strlen("Error\n"));
	write(2, str, ft_strlen(str));
	write(2, "\n" , 1);
	exit(EXIT_FAILURE);
}

void	parser(t_game *game, char **argv)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (!file_fd)
		exit_error("open file");
	if (parse_direction_and_color(game, file_fd))
		exit_error("direction_color");
	if (parse_map(game, file_fd))
		exit_error("map");

	(void) argv;
	temp_init_map(game);
}
