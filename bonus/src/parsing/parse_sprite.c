/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/27 18:11:32 by bperraud         ###   ########.fr       */
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
		obj->size = 1 / (double) ft_atoi(line_split[1]);
		obj->x = ft_atoi(line_split[index]) + 0.5;
		obj->y = ft_atoi(line_split[index + 1]) + 0.5;
		if (obj->x >= game->map.width || obj->y >= game->map.height)
			return (obj_index);
		game->list_sprite[obj_index] = obj;
		load_texture(game->mlx, line_split[0],
			&game->list_sprite[obj_index]->t);
		index += 2;
		obj_index++;
	}
	return (obj_index);
}

static void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
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
		free_split(line_split);
		line = get_next_non_empty_line(fd);
	}
}
