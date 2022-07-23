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

static int	is_line_empty(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '\n' || *line == '\r');
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

void	load_texture(t_game *game, char direction, char *path_to_texture)
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	if (direction == 'N')
	{
		img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures.no_wall.width, &game->textures.no_wall.height);
		game->textures.no_wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
	}
	else if (direction == 'E')
	{
		img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures.ea_wall.width, &game->textures.ea_wall.height);
		game->textures.ea_wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
	}
	else if (direction == 'W')
	{
		img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures.we_wall.width, &game->textures.we_wall.height);
		game->textures.we_wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
	}
	else if (direction == 'S')
	{
		img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->textures.so_wall.width, &game->textures.so_wall.height);
		game->textures.so_wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
	}
	if (img == (void *)0)
		exit_error("texture : file not valid");

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
		line = get_next_line(file_fd);
		height++;
	}
	game->map.width = width;
	game->map.height = height;
}

static void	parse_direction_and_color(t_game *game, int file_fd)
{
	char	*line;
	int		i;

	i = 0;
	// rajouter pour éviter doublons
	while (i++ < 6 && game)
	{
		line = gnl_not_empty(file_fd);
		if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E') && line[2] == ' ')
			load_texture(game, line[0], line + 3);
		else if (line[0] == 'F' && line[1] == ' ')
			parse_color(game, line + 1, 1);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_color(game, line + 1, 0);
		else
		{
			printf("line : %s\n", line);
			exit_error("unexpected caracter");
		}
		free(line);
	}
}

static int	parse_map(t_game *game, int file_fd)
{
	int encounter_player;

	encounter_player = 0;
	return (0);
}

void	parser(int argc, char **argv, t_game *game)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (!file_fd)
		exit_error("open file");

	parse_direction_and_color(game, file_fd);
	get_map_size(game, file_fd);

	printf("width : %li\n", game->map.width);
	printf("height : %li\n", game->map.height);

	//if (line[0] == '0' || line[0] == '1' || line[0] == ' ')
			//get_map_size(game, file_fd);

	if (parse_map(game, file_fd))
		exit_error("map");

	(void) argv;
	temp_init_map(game);
}
