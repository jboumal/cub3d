/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:04:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 16:00:40 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_ceiling(t_game *game, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	img = mlx_xpm_file_to_image(game->mlx, path_to_texture,
			&game->sky.width, &game->sky.height);
	if (!img)
		parsing_error("error when loading door texture");
	game->sky.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->sky.allocated_img = img;
	game->map.ceil = 1;
}

static int	parse_floor(t_game *game, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	img = mlx_xpm_file_to_image(game->mlx, path_to_texture,
			&game->floor.width, &game->floor.height);
	if (!img)
		parsing_error("error when loading door texture");
	game->floor.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->floor.allocated_img = img;
	game->map.floor = 1;
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
		parsing_error("invalid texture path");
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
		line = get_next_non_empty_line(fd);
		//if (is_token(line, "NO :SO :EA :WE ", ':', 3))
			//load_texture(game, line[0], skip_spaces(line + 3));
		if (isdigit(line[0]))
			load_texture(game, line[0], skip_spaces(line + 2));
		else if (!str_n_cmp("F ", line, 2))
			parse_floor(game, skip_spaces(line + 2));
		else if (!str_n_cmp("C ", line, 2))
			parse_ceiling(game, skip_spaces(line + 2));
		else
			parsing_error("invalid identifier");
		free(line);
	}
}
