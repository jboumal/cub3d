/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:18:46 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/17 18:45:42 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map_dimensions(char *map_str, t_game *g)
{
	size_t	width;

	width = 0;
	while (*map_str)
	{
		if (*map_str == '\n')
		{
			if (g->map.width < width)
				g->map.width = width;
			width = 0;
			g->map.height++;
		}
		else
			width++;
		map_str++;
	}
	g->map.height++;
}

static void	set_player(size_t i, size_t j, enum e_side direction, t_game *g)
{
	if (g->player.pos.x)
		parsing_error("mutiple player position in map");
	//g->player.pos = vector(j, i);
	g->player.pos = vector((double)j + 0.5, i - 0.1);
	g->player.dir.y = (direction == N) - (direction == S);
	g->player.dir.x = (direction == E) - (direction == W);
	g->player.plane.x = 0.66 * g->player.dir.y;
	g->player.plane.y = -0.66 * g->player.dir.x;
}

static void	parse_map_char(char map_char, int i, int j, t_game *g)
{
	if (map_char == '0')
		g->map.data[i * g->map.width + j] = 0;
	else if (isascii_48(map_char) && g->textures[map_char - 49].img)
		g->map.data[i * g->map.width + j] = map_char - 48;
	else if (ft_strchr("NSWE", map_char))
	{
		g->map.data[i * g->map.width + j] = 0;
		set_player(i, j, get_direction(map_char), g);
	}
	else if (ft_strchr(SPACES, map_char))
		g->map.data[i * g->map.width + j] = -1;
	else
		parsing_error("invalid character in map");
}

static void	init_map_data(t_game *g)
{
	size_t	i;

	i = 0;
	while (i < g->map.width * g->map.height)
	{
		g->map.data[i] = -1;
		i++;
	}
}

void	parse_map(char *map_str, t_game *g)
{
	size_t	i;
	size_t	j;

	fill_map_dimensions(map_str, g);
	g->map.data = x_malloc(g->map.width * g->map.height * sizeof(int));
	i = 0;
	init_map_data(g);
	while (i < g->map.height)
	{
		j = 0;
		while (*map_str != '\n' && *map_str)
		{
			parse_map_char(*map_str, i, j, g);
			j++;
			map_str++;
		}
			map_str += (*map_str == '\n');
		i++;
	}
	if (!g->player.pos.x)
		parsing_error("no player position given in map");
}
