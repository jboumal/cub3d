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

static void	add_wall(char *str, t_game *g)
{
	int		i;
	char	**arr;
	t_node	*node;

	arr = ft_split(str, ',');
	i = 0;
	while (arr[i])
	{
		node = new_node(x_calloc(1, sizeof(t_img)));
		load_texture(g->mlx, skip_spaces(arr[i] + 2), node->content);
		clst_add_back(&g->textures[str[0] - 49], node);
		i++;
	}
	str_arr_free(arr);
}

void	parse_textures(t_game *g, int fd)
{
	char		*line;
	t_dy_str	s;

	while (g->map.ceil == -1)
	{
		s = dy_str_new();
		line = get_next_non_empty_line(fd);
		dy_str_append_str(&s, line);
		free(line);
		while (ft_strchr(" \t\n\r", s.str[s.len - 1]))
			dy_str_pop_back(&s);
		if (isascii_48(s.str[0]) && s.str[0] != 'F' && s.str[0] != 'C')
			add_wall(s.str, g);
		else if (!str_n_cmp("F ", s.str, 2))
			load_texture(g->mlx, skip_spaces(s.str + 2), &g->floor);
		else if (!str_n_cmp("C ", s.str, 2))
		{
			load_texture(g->mlx, skip_spaces(s.str + 2), &g->sky);
			g->map.ceil = 1;
		}
		else
			exit_error("invalid identifier");
		dy_str_destroy(&s);
	}
}
