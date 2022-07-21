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

#include <stdio.h>

// Temporary function to be deleted when parsing works.
void	temp_init_map(t_game *game)
{
	static int	map[49] = {
		1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1,
	};

	game->map.data = map;
	game->map.width = 7;
	game->map.height = 7;
	game->player.pos.x = 3;
	game->player.pos.y = 3;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
}

static char	*gnl_not_empty(int file_fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(file_fd);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\r')
	{
		free(line);
		return (gnl_not_empty(file_fd));
	}
	else
		return (line);
}

void	exit_error(char *str)
{
	write(2, "Error\n" , ft_strlen("Error\n"));
	write(2, str, ft_strlen(str));
	write(2, "\n" , 1);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	res;

	neg = 1;
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((res * 10 > INT_MAX) && neg == 1)
			return (-1);
		if ((res * 10 - 1 > INT_MAX) && neg == -1)
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((int)(res * neg));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	isdigit(int c)
{
	return (c >= '0' && c <= '9');
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
				break;
			if (i > 2)
				exit_error("color : number too big");
			if (!isdigit(*line))
				exit_error("color : not a valid digit");
			color[nb_color][i] = *line;
			i++;
		}
		color[nb_color][i] = '\0';
		nb_color++;
	}
	if (is_floor)
		game->map.floor = create_trgb(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	else
		game->map.ceil = create_trgb(0, ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
}

void	load_texture(t_game *game, char *path_to_texture)
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures.wall.width, &game->textures.wall.height);
	if (img == (void *)0)
		exit_error("texture : file not valid");
	game->textures.wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
}

static int	parse_direction_and_color(t_game *game, int file_fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i++ < 6 && game)
	{
		line = gnl_not_empty(file_fd);
		if (line[0] == 'N' )
			load_texture(game, line + 3);
		else if (line[0] == 'S')
			;
		else if (line[0] == 'W')
			;
		else if (line[0] == 'E')
			;
		else if (line[0] == 'F' && line[1] == ' ')
			parse_color(game, line + 1, 1);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_color(game, line + 1, 0);
		free(line);
	}
	return (0);
}

static int	parse_map(t_game *game, int file_fd)
{
	return (0);
}

void	parser(int argc, char **argv, t_game *game)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (!file_fd)
		exit_error("open file");
	if (parse_direction_and_color(game, file_fd))
		exit_error("direction_color");
	if (parse_map(game, file_fd))
		exit_error("map");

	(void) argv;
	temp_init_map(game);
}
