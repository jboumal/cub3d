/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:10:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/29 22:29:07 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_rect(t_rect *rect, t_vector pos, int width, int height)
{
	rect->x = pos.x;
	rect->y = pos.y;
	rect->width = width;
	rect->height = height;
	rect->color = 0;
}

static void	render_background(t_img *img, t_game *game)
{
	int			i;
	int			j;
	t_rect		rect;
	t_vector	pos;

	i = SCREEN_H - UI_H;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			my_mlx_pixel_put(img, j, i, UI_COLOR2);
			j++;
		}
		i++;
	}
	pos = vector(SCREEN_W / 2 - game->title.hud.width / 2, SCREEN_H - UI_H);
	create_rect(&rect, vector(0, 0), game->title.hud.width,
		game->title.hud.height);
	blt_dst(&game->title.hud, img, pos, rect);
}

static void	draw_number(t_game *game, int d, t_img *img, t_vector pos)
{
	t_rect	r;
	int		w;

	w = 32;
	if (d >= 100)
	{
		d = 100;
		create_rect(&r, vector(0, 0), w, game->title.chars.height);
		blt_dst(&game->title.chars, img, pos, r);
		pos.x -= w;
		blt_dst(&game->title.chars, img, pos, r);
		r.x += w;
		pos.x -= w;
		blt_dst(&game->title.chars, img, pos, r);
		return ;
	}
	create_rect(&r, vector(w * (d % 10) + 1, 0), w, game->title.chars.height);
	blt_dst(&game->title.chars, img, pos, r);
	if (d >= 10)
	{
		pos.x -= w;
		create_rect(&r, vector(w * (d / 10) + 1, 0), w,
			game->title.chars.height);
		blt_dst(&game->title.chars, img, pos, r);
	}
}

static void	render_number(t_img *img, t_game *game)
{
	t_vector	pos;
	int			ammo;

	ammo = game->list_active_gun[game->active_gun]->ammo;
	pos = vector(SCREEN_W / 2 + 230, SCREEN_H - UI_H + 58);
	if (!game->list_active_gun[game->active_gun]->is_knife)
		draw_number(game, ammo, img, pos);
	pos.x = SCREEN_W / 2 + 87;
	draw_number(game, 100, img, pos);
	pos.x = SCREEN_W / 2 - 280;
	draw_number(game, 0, img, pos);
	pos.x = SCREEN_W / 2 - 500;
	draw_number(game, 1, img, pos);
}

void	render_ui(t_img *img, t_game *game)
{
	render_background(img, game);
	render_number(img, game);
	render_minimap(img, game);
}
