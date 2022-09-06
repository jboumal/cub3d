/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/06 20:16:53 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define NOT_PIXEL 9961608
# define STILL_NOT_PIXEL 10158219
# define MIN_DIST 0.5
# define MAX_DIST 20
# define GUN_PATH "img/sprite/gun/"
# define EXTENSION "x.xpm"

typedef   void (*spr_action)(t_game *game, t_sprite *gun);

enum e_gun
{
	PISTOL,
	MACH,
	SULF,
	KNIFE
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
	double		dist_to_plane;
	double		x_end;
	double		y_end;
	int			pixel_size;
	int			col;
	bool		is_collect;
	bool		is_in_fov;
	spr_action  collect_action;
	enum e_gun  enum_gun;
	t_texture	t;
	t_texture	anim;
}	t_sprite;

/* sprite */
void	render_sprites(t_game *game);

/* draw sprite */
void	compute_field_sprite(t_game *g);
void	draw_sprite(t_game *g, t_sprite *s, t_texture *t, int n_image);

/* gun */
void	switch_gun(t_game *game);
void	replace_gun(t_game *game, t_sprite *gun);
void	init_gun(t_game *game);
void	render_gun(t_game *game);

#endif

