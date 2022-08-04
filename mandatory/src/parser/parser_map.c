/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:18:46 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/04 20:30:02 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

char	*get_map_str(int fd)
{
	t_dy_str	dy_str;
	char		*line;
	char		*ptr;

	dy_str = dy_str_new();
	line = gnl_not_empty(fd);
	while (line)
	{
		ptr = line;
		while (*ptr)
		{
			if (*ptr != '\r')
				dy_str_append_c(&dy_str, *ptr);
			ptr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	while (strchr(" \n\t", dy_str.str[dy_str.len - 1]))
	{
		dy_str.str[dy_str.len - 1] = '\0';
		dy_str.len--;
	}
	return (dy_str.str);
}

void	fill_map_dimensions(char *map_str, t_game *g)
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

void parse_map(char *map_str, t_game *g)
{
	int i = 0;
	int j;
	int player_index;

	fill_map_dimensions(map_str, g);
	g->map.data = malloc(g->map.width * g->map.height * sizeof(int));
	int *ptr = g->map.data;
	i = 0;
	for (int k = 0; k < g->map.width * g->map.height; k++)
		g->map.data[k] = -1;
	while (i < g->map.height)
	{
		j = 0;
		while (*map_str != '\n' && *map_str)
		{
			if (*map_str == '1')
				g->map.data[i * g->map.width + j] = 1;
			else if (*map_str == '0')
				g->map.data[i * g->map.width + j] = 0;
			else if (strchr("NSWE", *map_str))
			{
				g->map.data[i * g->map.width + j] = 0;
				g->player.pos = vector(j, i);
			}
			else
				g->map.data[i * g->map.width + j] = -1;
			j++;
			*map_str++;
		}
			map_str += (*map_str == '\n');
		i++;
	}
	g->player.dir = vector(0, 1);
}
