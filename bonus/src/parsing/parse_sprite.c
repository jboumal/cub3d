/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:03:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/29 14:05:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_x(t_sprite *s)
{
	int	lx;
	int	ly;
	int	color;
	int	x_start_bound;

	lx = 0;
	x_start_bound = 0;
	while (lx++ < s->t.width)
	{
		ly = 0;
		while (ly++ < s->t.height)
		{
			color = mlx_get_pixel(&s->t.data, lx, ly);
			if (color != NOT_PIXEL && color > 0)
			{
				s->x_start = (double)(lx + 1) / s->t.width;
			}
		}
	}
}

static void	end_y(t_sprite *s)
{
	int	lx;
	int	ly;
	int	color;
	int	y_start;

	lx = 0;
	y_start = s->t.height;
	while (lx++ < s->t.width)
	{
		ly = 0;
		while (ly++ < s->t.height)
		{
			color = mlx_get_pixel(&s->t.data, lx, ly);
			if ((color != NOT_PIXEL && color > 0) && ly < y_start)
				y_start = ly + 1;
		}
	}
	s->y_start =  (double) (y_start) / (double) s->t.height;
}

static int	create_sprite(t_game *game, char **line_split, int s_index)
{
	t_sprite	*s;
	int			index;

	index = 2;
	while (line_split[index])
	{
		s = x_malloc(sizeof(t_sprite));
		s->x = ft_atoi(line_split[index]);
		s->is_collect = ft_atoi(line_split[1]);
		if (!line_split[index + 1])
			return (s_index);
		s->y = ft_atoi(line_split[index + 1]);
		if (s->x >= game->map.width || s->y >= game->map.height
			|| game->map.data[(int) (s->y * game->map.width + s->x)] != 0)
		{
			index += 2;
			continue;
		}
		s->x += 0.5;
		s->y += 0.5;
		game->list_sprite[s_index] = s;
		load_texture(game->mlx, line_split[0], &game->list_sprite[s_index]->t);
		index += 2;
		s_index++;
		start_x(s);
		end_y(s);
		//printf("pourcentage : %f\n", s->x_start);
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
		s_index = create_sprite(game, line_split, s_index);
		free(line);
		str_arr_free(line_split);
		line = get_next_non_empty_line(fd);
	}
}
