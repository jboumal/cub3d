/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:19:48 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/01 19:22:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

# define TILEMAP_SIZE 12
# define H 128

enum e_side
{
	N,
	E,
	S,
	W
};

typedef struct s_ray
{
	double		wall_dist;
	t_vector	dir;
	int			cell;
	enum e_side	side;
}	t_ray;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_draw_line_var
{
	int		tex_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_ray	*ray;
}	t_draw_line_var;

/*init*/
void	load_textures(t_game *game);

/*dda*/
void	dda(t_ray *ray, t_game *game);

/*minimap*/
void	render_minimap(t_data *img, t_game *game);

/*mlx_utils*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data	get_new_img(t_game *game);

/*raycasting*/
void	raycasting(int x, t_data *img, t_game *game);

/*render*/
void	render(t_game *game);

#endif
