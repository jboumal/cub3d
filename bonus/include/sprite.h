/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/04 18:16:57 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define NOT_PIXEL 9961608
# define MIN_DIST 0.7
# define MAX_DIST 20
# define GUN_PATH "img/sprite/gun/"
# define EXTENSION "x.xpm"

typedef   void (*spr_action)(t_game *game, t_sprite *gun);

enum e_gun
{
	pistol,
	mach,
	sulf,
	knife
};

typedef struct s_sprite
{
	double		x;
	double		y;
	double		height;
	double		width;
	double		ceil;
	double		angle;
	double		dist_to_p;
	double		x_end;
	double		y_end;
	int			pixel_size;
	int			col;
	bool		is_collect;
	bool		is_in_fov;
	spr_action  action;
	t_texture	t;
	t_texture	anim[5];
}	t_sprite;

/* sprite */
void	render_sprites(void	*img, t_game *game);

/* draw sprite */
void	compute_field_sprite(t_game *g);
void	draw_sprite(t_game *g, void *img, t_sprite *s, t_texture *t);

/* gun */
void	init_gun(t_game *game);
void	render_gun(void *img, t_game *game);

#endif

