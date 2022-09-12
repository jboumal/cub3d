/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/10 01:30:52 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define NOT_PIXEL 9961608
# define STILL_NOT_PIXEL -16777216
# define MIN_DIST 0.5
# define MAX_DIST 20

typedef void	(*t_spr_action)(t_game *game, t_sprite *gun);

enum e_gun
{
	PISTOL,
	MACH,
	GATLING,
	KNIFE
};

typedef struct s_sprite
{
	double			x;
	double			y;
	double			height;
	double			width;
	double			ceil;
	double			angle;
	double			dist_to_p;
	double			dist_to_plane;
	double			x_end;
	double			y_end;
	int				pixel_size;
	int				col;
	bool			is_collect;
	bool			is_in_fov;
	t_spr_action	collect_action;
	enum e_gun		enum_gun;
	double			image;
	t_texture		t;
}	t_sprite;

typedef struct s_gun
{
	t_sprite		sprite;
	double			image;
	enum e_gun		enum_gun;
}	t_gun;


/* sprite */
void	light_window(t_game *g);
void	render_sprites(t_game *game);

/* draw sprite */
void	compute_field_sprite(t_game *g);
void	draw_sprite(t_game *g, t_sprite *s, t_texture *t, int n_image);

/* gun */
void	anim_gun(t_game *game);
void	switch_gun(t_game *game);
void	replace_gun(t_game *game, t_sprite *gun);
void	init_gun(t_game *game);
void	render_gun(t_game *game);

#endif

