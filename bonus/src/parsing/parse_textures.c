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

void	parse_textures(t_game *g, int fd)
{
	t_dy_str	line;

	while (g->map.ceil == -1)
	{
		line = dy_str_new();
		dy_str_append_str(&line, get_next_non_empty_line(fd));
		while (ft_strchr(" \t\n\r", line.str[line.len - 1]))
			dy_str_pop_back(&line);
		if (isascii_48(line.str[0]) && line.str[0] != 'F' && line.str[0] != 'C')
			load_texture(
				g->mlx, skip_spaces(line.str + 2),
				&g->textures[line.str[0] - 49]);
		else if (!str_n_cmp("F ", line.str, 2))
			load_texture(g->mlx, skip_spaces(line.str + 2), &g->floor);
		else if (!str_n_cmp("C ", line.str, 2))
		{
			load_texture(g->mlx, skip_spaces(line.str + 2), &g->sky);
			g->map.ceil = 1;
		}
		else
			exit_error("invalid identifier");
		dy_str_destroy(&line);
	}
	load_texture(g->mlx, "img/rain.xpm", &g->rain);
}
