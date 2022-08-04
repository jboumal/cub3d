/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:04:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/05 00:07:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static enum e_side	get_direction(char c)
{
	if (c == 'N')
		return (N);
	if (c == 'E')
		return (E);
	if (c == 'S')
		return (S);
	return (W);
}

static int	parse_color(t_game *game, char *line)
{
	int		color;
	int		i;
	char	**arr;

	arr = ft_split(line, ',');
	i = 0;
	color = 0;
	while (arr[i])
	{
		color <<= 8;
		color += ft_atoi(arr[i]);
		i++;
	}
	str_arr_free(arr);
	return (color);
}

static void	load_texture(t_game *game, char direction, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;
	enum e_side	side;

	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	side = get_direction(direction);
	img = mlx_xpm_file_to_image(
			game->mlx,
			path_to_texture,
			&game->textures[side].width,
			&game->textures[side].height);
	if (!img)
		exit(EXIT_FAILURE);
	game->textures[side].img = (unsigned int *)mlx_get_data_addr(
			img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->textures[side].allocated_img = img;
}

static bool	is_full(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img)
			return (false);
		i++;
	}
	return (game->map.floor > -1 && game->map.ceil > -1);
}

void	parse_textures(t_game *game, int fd)
{
	char	*line;

	while (!is_full(game))
	{
		line = get_first_non_empty_line(fd);
		if (is_token(line, "NO :SO :EA :WE ", ':', 3))
			load_texture(game, line[0], skip_spaces(line + 3));
		else if (!str_n_cmp("F ", line, 2))
			game->map.floor = parse_color(game, skip_spaces(line + 1));
		else if (!str_n_cmp("C ", line, 2))
			game->map.ceil = parse_color(game, skip_spaces(line + 1));
		else
			exit(EXIT_FAILURE);
		free(line);
	}
}
