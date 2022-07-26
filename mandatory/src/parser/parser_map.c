/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:18:46 by bperraud          #+#    #+#             */
/*   Updated: 2022/07/26 16:10:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void	place_player(t_game *game, char direction, int x, int y)
{
	if (direction == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if (direction == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	else if (direction == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
	else if (direction == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	game->player.pos.x = x;
	game->player.pos.y = y;
}

int	parse_map(t_game *game, int file_fd, char *line)
{
	int		encounter_player;
	int		*map;
	size_t	x;
	size_t	y;

	encounter_player = 0;
	map = malloc(game->map.width * game->map.height * sizeof(int));
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (x >= ft_strlen(line) - 2)
				map[x + (game->map.width * y)] = -1;
			else if (line[x] == ' ')
				map[x + (game->map.width * y)] = -1;
			else if (line[x] == 'N' || line[x] == 'E' || line[x] == 'W' || line[x] == 'S')
			{
				if (encounter_player)
					exit_error("double player position");
				encounter_player = 1;
				map[x + (game->map.width * y)] = 0;
				place_player(game, line[x], x, y);
			}
			else if (line[x] == '0' || line[x] == '1')
				map[x + (game->map.width * y)] = line[x] - 48;
			else
				exit_error("wrong character in map");
			x++;
		}
		y++;
		line = get_next_line(file_fd);
		if (is_line_empty(line))
			exit_error("empty line in map");
	}
	if (!encounter_player)
		exit_error("missing player position in map");
	game->map.data = map;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0;
	return (0);
}
