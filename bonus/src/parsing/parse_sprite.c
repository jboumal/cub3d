/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/26 17:34:04 by vrogiste         ###   ########.fr       */
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

static void	add_action_object(t_object *obj, char *sprite_name)
{
	if (!str_n_cmp(sprite_name, "machinegun.xpm", strlen(sprite_name)))
	{
		obj->collect_action = &replace_gun;
		obj->enum_gun = MACH;
	}
	else
		obj->collect_action = NULL;
}

static int	init_object(t_game *game, char **line_split, int s_index)
{
	t_object	*obj;
	int			index;

	index = 2;
	while (line_split[index])
	{
		obj = x_malloc(sizeof(t_object));
		load_texture(game->mlx, line_split[0], &obj->s.t);
		obj->collect_action = NULL;
		obj->s.x = ft_atoi(line_split[index]) + 0.5;
		obj->s.y = ft_atoi(line_split[index + 1]) + 0.5;
		if (game->map.data[(int)((obj->s.y - 0.5) * game->map.width + obj->s.x - 0.5)]
		!= 0 || obj->s.x - 0.5 >= game->map.width || obj->s.y - 0.5 >= game->map.height)
		{
			index += 2;
			continue ;
		}
		if (ft_atoi(line_split[1]))
		{
			game->list_collect[s_index] = obj;
			obj->game_index = s_index;
			add_action_object(obj, line_split[0] + 11);
			game->map.object_map[(int)((obj->s.y - 0.5) * game->map.width + obj->s.x - 0.5)] = 2;
		}
		else
			game->map.object_map[(int)((obj->s.y - 0.5) * game->map.width + obj->s.x - 0.5)] = 1;
		bound_start(&obj->s, obj->s.t);
		game->list_object[s_index] = obj;
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
		s_index = init_object(game, line_split, s_index);
		free(line);
		str_arr_free(line_split);
		line = get_next_non_empty_line(fd);
	}
	init_gun(game);
}
