/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:19:48 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/17 15:46:30 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

enum e_side
{
	N,
	E,
	S,
	W
};

typedef struct s_scanline
{
	t_vector	step;
	t_vector	floor;
}	t_scanline;

typedef struct s_ray
{
	double		dist;
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
	int				tx;
	int				line_height;
	int				draw_start;
	int				draw_end;
	t_texture		*tex;
	t_ray			*ray;
}	t_draw_line_var;

typedef struct s_th_arg
{
	int		i;
	void	*data[3];
}	t_th_arg;

/* dda */
void	dda(t_ray *ray, t_game *game);

/* floorcasting */
void	floorcasting(int y0, int y1, t_data *img, t_game *game);

/* minimap */
void	render_minimap(t_data *img, t_game *game);

/* raincasting */
void	raincasting(int x0, int x1, t_data *img, t_game *g);

/* raycasting */
void	raycasting(int x0, int x1, t_data *img, t_game *game);

/* render */
void	render(t_game *game);
void	load_floor_texture(t_game *game);

/* routines */
int		get_start(int i, int start, int end);
int		get_end(int i, int start, int end);
void	*routine_floor(void *arg);
void	*routine_sky(void *arg);
void	*routine_wall(void *arg);
void	*routine_rescale(void *arg);

/* skycasting */
void	load_sky_texture(t_game *game);
void	skycasting(int x0, int x1, t_data *img, t_game *g);

/* sort sprite */
void	sort_sprite(t_game *g, t_sprite *obj, int i);

/* sprite */
void	init_sprite(t_game *game);
void	render_sprites(void	*img, t_game *game);

#endif
