/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_sprite(t_game *game, char **line_split, int obj_index)
{
	t_sprite	*obj;
	int			index;

	index = 2;
	while (line_split[index])
	{
		obj = x_malloc(sizeof(t_sprite));
		obj->x = ft_atoi(line_split[index]);
		obj->is_collect = ft_atoi(line_split[1]);
		if (!line_split[index + 1])
			return (obj_index);
		obj->y = ft_atoi(line_split[index + 1]);
		if (obj->x >= game->map.width || obj->y >= game->map.height
			|| game->map.data[(int) (obj->y * game->map.width + obj->x)] != 0)
		{
			index += 2;
			continue;
		}
		obj->x += 0.5;
		obj->y += 0.5;
		game->list_sprite[obj_index] = obj;
		load_texture(game->mlx, line_split[0], &game->list_sprite[obj_index]->t);
		index += 2;
		obj_index++;
	}
	return (obj_index);
}

void	parse_sprite(t_game *game, int fd)
{
	char	*line;
	char	**line_split;
	int		obj_index;

	line = get_next_non_empty_line(fd);
	obj_index = 0;
	while (line)
	{
		line_split = ft_split(line, ' ');
		obj_index = create_sprite(game, line_split, obj_index);
		free(line);
		str_arr_free(line_split);
		line = get_next_non_empty_line(fd);
	}
}
