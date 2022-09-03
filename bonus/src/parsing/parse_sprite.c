/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/03 15:58:38 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bound_start(t_sprite *s, t_texture text)
{
	int		lx;
	int		ly;
	int		y_end;
	int		x_end;

	y_end = text.height;
	x_end = text.width;
	lx = -1;
	while (++lx < text.width)
	{
		ly = -1;
		while (++ly < text.height)
		{
			if (mlx_get_pixel(&text.data, lx, ly) != NOT_PIXEL)
			{
				if (lx < x_end)
					x_end = lx + 1;
				if (ly < y_end)
					y_end = ly + 1;
			}
		}
	}
	s->y_end = y_end / (double) text.height;
	s->x_end = x_end / (double) text.width;
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
		s->x = ft_atoi(line_split[index]) + 0.5;
		s->y = ft_atoi(line_split[index + 1]) + 0.5;
		if (game->map.data[(int)((s->y - 0.5) * game->map.width + s->x - 0.5)]
		!= 0 || s->x - 0.5 >= game->map.width || s->y - 0.5 >= game->map.height)
		{
			index += 2;
			continue ;
		}
		s->x_end = 0;
		s->y_end = 0;
		bound_start(s, s->t);
		game->list_sprite[s_index] = s;
		index += 2;
		s_index++;
	}
	return (s_index);
}

static void	init_gun(t_game *game)
{
	t_sprite	*gun;

	gun = x_malloc(sizeof(t_sprite));
	gun->dist_to_p = 0;
	gun->angle = 0;
	gun->x_end = 0;
	gun->y_end = 0;
	load_texture(game->mlx, "img/sprite/gun/pistol0.xpm", &gun->t);
	game->list_sprites[0] = gun;
	game->list_active_gun[0] = gun;
	bound_start(gun, gun->t);
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
