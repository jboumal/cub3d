/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:12 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 21:50:08 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

# define SCREEN_W 1920
# define SCREEN_H 1080
# define SCREEN_TITLE "cub3d"

# define K_PRESS_EVENT 2
# define K_RELEASE_EVENT 3
# define DESTROY_NOTIFY_EVENT 17

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

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

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
}	t_game;

int			game_loop(t_game *game);
int			key_down(int code, t_game *game);
int			key_release(int code, t_game *game);
void		parser(t_game *game, char **argv);
void		render(t_game *game);

/*utils*/
t_vector	vector(double x, double y);

/*mlx_utils*/

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data		get_new_img(t_game *game);

double		dda(t_vector ray_dir, int *side, t_game *game);

void		raycasting(int x, t_data *img, t_game *game);

void		*ft_memset(void *b, int c, size_t len);

#endif
