/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/12 04:17:49 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bound_start(t_sprite *s, t_img text)
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
			if (mlx_get_pixel(&text, lx, ly) != NOT_PIXEL)
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

static void	add_action_sprite(t_sprite *s, char *sprite_name)
{
	if (!str_n_cmp(sprite_name, "machinegun.xpm", strlen(sprite_name)))
	{
		s->collect_action = replace_gun;
		s->enum_gun = MACH;
	}
}

static int	init_sprite(t_game *game, char **line_split, int s_index)
{
	t_sprite	*s;
	int			index;

	index = 2;
	while (line_split[index])
	{
		s = x_malloc(sizeof(t_sprite));
		s->t = get_img_from_xpm(game->mlx, line_split[0]);
		s->is_collect = ft_atoi(line_split[1]);
		s->collect_action = NULL;
		s->x = ft_atoi(line_split[index]) + 0.5;
		s->y = ft_atoi(line_split[index + 1]) + 0.5;
		if (game->map.data[(int)((s->y - 0.5) * game->map.width + s->x - 0.5)]
		!= 0 || s->x - 0.5 >= game->map.width || s->y - 0.5 >= game->map.height)
		{
			index += 2;
			continue ;
		}
		if (s->is_collect)
		{
			add_action_sprite(s, line_split[0] + 11);
			game->map.object_map[(int)((s->y - 0.5) * game->map.width + s->x - 0.5)] = 2;
		}
		else
			game->map.object_map[(int)((s->y - 0.5) * game->map.width + s->x - 0.5)] = 1;
		bound_start(s, s->t);
		game->list_sprite[s_index] = s;
		index += 2;
		s_index++;
	}
	return (s_index);
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
		s_index = init_sprite(game, line_split, s_index);
		free(line);
		str_arr_free(line_split);
		line = get_next_non_empty_line(fd);
	}
	init_gun(game);
}
