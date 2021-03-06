/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/01 19:59:16 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include "textures.h"
# include <fcntl.h>

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

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_state		state;
	t_textures	textures;
}	t_game;

/*parser*/
void	parser(char **argv, t_game *game);

/*parser_map*/
int		*parse_map(t_game *game, int file_fd, char *line);

/*utils*/
int		create_trgb(int t, int r, int g, int b);
char	*skip_spaces(char *str);
int		is_line_empty(char *line);
char	*gnl_not_empty(int file_fd);
void	exit_error(char *str, char *line);

#endif
