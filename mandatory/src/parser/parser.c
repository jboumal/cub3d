/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:38 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 22:02:54 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*first_map_line(int file_fd, char *path_to_map)
{
	char	*line;
	int		i;

	i = 0;
	close(file_fd);
	file_fd = open(path_to_map, O_RDONLY);
	line = gnl_not_empty(file_fd);
	while (i++ < 6)
	{
		free(line);
		line = gnl_not_empty(file_fd);
	}
	return (line);
}

void	parse_color(t_game *game, char *line, int is_floor)
{
	char	color[3][4];
	int		i;
	int		nb_color;

	nb_color = 0;
	while (nb_color != 3)
	{
		i = 0;
		while (*line++)
		{
			if ((*line == ',' && nb_color < 2) || ((*line == '\n' || *line == '\r') && nb_color == 2))
				break ;
			if (*line < '0' || *line > '9')
				exit_error("color : not a valid digit", NULL);
			color[nb_color][i] = *line;
			i++;
		}
		color[nb_color][i] = '\0';
		if (ft_atoi(color[nb_color]) > 255)
			exit_error("color : number bigger than 255", NULL);
		nb_color++;
	}
	if (is_floor)
		game->map.floor = create_trgb(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	else
		game->map.ceil = create_trgb(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
}

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

void	load_texture(t_game *game, char direction, char *path_to_texture)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*img;
	enum e_side side;

	path_to_texture[str_len(path_to_texture) - 2] = '\0';
	side = get_direction(direction);
	img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures[side].width, &game->textures[side].height);
	if (!img)
		exit_error("texture : path_to_texture not valid", NULL);
	game->textures[side].img = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian );
}

static void	get_map_size(t_game *game, int file_fd)
{
	char	*line;
	size_t	width;
	size_t	height;
	size_t	i;

	i = 0;
	height = 0;
	width = 0;
	line = gnl_not_empty(file_fd);
	while (line)
	{
		i = 0;
		while (line[i] != '\n' && line[i] != '\r')
		{
			if ((line[i] == '0' || line[i] == '1') && i >= width)
				width = i + 1;
			i++;
		}
		free(line);
		line = get_next_line(file_fd);
		height++;
	}
	game->map.width = width;
	game->map.height = height;
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

static void	parse_direction_and_color(t_game *game, int file_fd)
{
	char	*line;

	while (!is_full(game))
	{
		line = gnl_not_empty(file_fd);
		if (is_token(line, "NO :SO :EA :WE ", ':', 3))
			load_texture(game, line[0], skip_spaces(line + 3));
		else if (!str_n_cmp("F ", line, 2))
			parse_color(game, skip_spaces(line + 1), 1);
		else if (!str_n_cmp("C ", line, 2))
			parse_color(game, skip_spaces(line + 1), 0);
		else
			exit_error("direction and color : unexpected caracter", line);
		free(line);
	}
}

void	parser(char **argv, t_game *game)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
		exit_error("open file", NULL);
	parse_direction_and_color(game, file_fd);
	get_map_size(game, file_fd);
	game->player.pos.x = 0;
	game->map.data = parse_map(game, file_fd, first_map_line(file_fd, argv[1]));
	if (!game->player.pos.x)
		exit_error("missing player position in map", NULL);
	game->player.plane.x = 0.66;
	game->player.plane.y = 0;
}
