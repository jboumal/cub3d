/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:04:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 18:50:06 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_ceiling_t(t_game *game, char *path_to_texture)
{
	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	load_texture(game->mlx, path_to_texture, &game->sky);
	game->map.ceil = 1;
}

static void	load_floor_t(t_game *game, char *path_to_texture)
{
	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	load_texture(game->mlx, path_to_texture, &game->floor);
}

static void	load_wall_t(t_game *game, int chara, char *path_to_texture)
{
	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	load_texture(game->mlx, path_to_texture, &game->textures[chara]);
}

void	parse_textures(t_game *game, int fd)
{
	char	*line;

	while (game->map.ceil == -1)
	{
		line = get_next_non_empty_line(fd);
		if (isascii_48(line[0]) && line[0] != 'F' && line[0] != 'C')
			load_wall_t(game, line[0] - 49, skip_spaces(line + 2));
		else if (!str_n_cmp("F ", line, 2))
			load_floor_t(game, skip_spaces(line + 2));
		else if (!str_n_cmp("C ", line, 2))
			load_ceiling_t(game, skip_spaces(line + 2));
		else
			exit_error("invalid identifier");
		free(line);
	}
}
