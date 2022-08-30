/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 02:40:00 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bound_start(t_sprite *s)
{
	int		lx;
	int		ly;
	int		color;
	int		y_start;

	lx = -1;
	y_start = s->t.height;
	s->x_start = 0;
	while (lx++ < s->t.width - 1)
	{
		ly = -1;
		while (ly++ < s->t.height - 1)
		{
			color = mlx_get_pixel(&s->t.data, lx, ly);
			if (color != NOT_PIXEL && color > 0)
			{
				if (!s->x_start)
					s->x_start = lx / (double) s->t.width;
				if (ly < y_start)
					y_start = ly;
			}
		}
	}
	s->y_start = y_start / (double) s->t.height;
}

static int	create_sprite(t_game *game, char **line_split, int s_index)
{
	t_sprite	*s;
	int			index;

	index = 2;
	while (line_split[index])
	{
		s = x_malloc(sizeof(t_sprite));
		load_texture(game->mlx, line_split[0], &s->t);
		s->is_collect = ft_atoi(line_split[1]);
		s->x = ft_atoi(line_split[index]);
		s->y = ft_atoi(line_split[index + 1]);
		if (s->x >= game->map.width || s->y >= game->map.height
			|| game->map.data[(int)(s->y * game->map.width + s->x)] != 0)
		{
			index += 2;
			continue ;
		}
		s->x += 0.5;
		s->y += 0.5;
		bound_start(s);
		game->list_sprite[s_index] = s;
		index += 2;
		s_index++;
	}
	return (s_index);
}

static void	init_gun(t_game *game)
{
	t_gun	*gun;

	gun = x_malloc(sizeof(t_gun));
	load_texture(game->mlx, "img/sprite/pistol.xpm", &gun->hold);
	game->list_guns[0] = gun;
	game->list_active_gun[0] = gun;
}

void	parse_sprite(t_game *game, int fd)
{
	char	*line;
	char	**line_split;
	int		s_index;

	line = get_next_non_empty_line(fd);
	s_index = 0;
	while (line)
	{
		line_split = ft_split(line, ' ');
		s_index = create_sprite(game, line_split, s_index);
		free(line);
		str_arr_free(line_split);
		line = get_next_non_empty_line(fd);
	}
	init_gun(game);
}
