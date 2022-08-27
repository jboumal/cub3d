/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:47:38 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 18:10:24 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define SPACES " \t"
# define TEXTURES_MAX 79

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
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		fov;
}	t_player;

typedef struct s_door
{
	int		cell;
	bool	opened;
	double	ratio;
}	t_door;

typedef struct s_state
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	r_left;
	bool	r_right;
	int		m_left;
	int		m_right;
	t_list	doors;
}	t_state;

typedef struct s_texture
{
	t_data	data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		size;
	double		height;
	double		width;
	double		ceil;
	double		angle;
	double		dist_to_p;
	bool		is_in_fov;
	t_texture	t;
}	t_sprite;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			img_w;
	int			img_h;
	t_map		map;
	t_player	player;
	t_state		state;
	t_list		textures[TEXTURES_MAX];
	t_texture	floor;
	t_texture	sky;
	t_sprite	*list_sprite[10];
	double		depth_buf[SCREEN_W];
}	t_game;

/* check_map */
void		check_map(t_game *g);

/* get_map_str */
char		*get_map_str(int fd);

/* parse_map */
void		parse_map(char *map_str, t_game *g);

/* parse_textures */
void		parse_textures(t_game *game, int fd);

/* parse_sprite */
void		parse_sprite(t_game *game, int fd);

/* parse */
enum e_side	get_direction(char c);
void		parse(int argc, char **argv, t_game *game);

/* mlx mouse */
int			mouse_hide(t_game *game);
int			mouse_move(t_game *game, int x, int y);

/* linux mouse function */
void		my_mouse_hook(t_game *game);

#endif
