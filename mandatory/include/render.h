/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:19:48 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 14:29:33 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

# define TILEMAP_SIZE 12

enum e_side
{
	N,
	E,
	S,
	W
};

typedef struct s_face
{
	int			cell;
	enum e_side	side;
}	t_face;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

/*dda*/
double	dda(t_vector ray_dir, t_face *face, t_game *g);

/*minimap*/
void	render_minimap(t_data *img, t_game *game);

/*mlx_utils*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data	get_new_img(t_game *game);

/*raycasting*/
void	raycasting(int x, t_data *img, t_game *g);

/*render*/
void	render(t_game *game);

#endif
