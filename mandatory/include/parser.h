/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 22:26:31 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

# define SPACES " \t"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	int		*data;
	size_t	width;
	size_t	height;
	int		ceil;
	int		floor;
	t_data	*no;
	t_data	*so;
	t_data	*we;
	t_data	*ea;
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_state
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_state;

typedef struct s_texture
{
	unsigned int	*img;
	int				width;
	int				height;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_state		state;
	t_texture	textures[4];
}	t_game;

/* get_map_str */
char	*get_map_str(int fd);

/* parse_map */
void	parse_map(char *map_str, t_game *g);

/* parse_textures */
void	parse_textures(t_game *game, int fd);

/* parse */
void	parser(char **argv, t_game *game);

#endif
