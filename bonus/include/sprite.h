/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 19:44:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define NOT_PIXEL 9961608
# define MIN_SPRITE_DIST 0.7

typedef struct s_sprite
{
	double		x;
	double		y;
	double		height;
	double		width;
	double		ceil;
	double		angle;
	double		dist_to_p;
	double		x_start;
	double		y_start;
	int			pixel_size;
	int			col;
	bool		is_collect;
	bool		is_in_fov;
	t_texture	t;
}	t_sprite;

/* sprite */
void	render_sprites(void	*img, t_game *game);

/* draw sprite */
void	compute_field_sprite(t_game *g);
void	draw_sprite(t_game *g, void *img, t_sprite *s);

/* gun */
void	render_gun(void *img, t_game *game);

#endif

