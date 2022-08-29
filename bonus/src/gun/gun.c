/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@guntudent.gun19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 00:05:32 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_gun(t_game *g, void *img, t_gun *gun)
{
	int		color;
	int		col;
	int		lx;
	int		ly;

	lx = 0;
	while (lx++ < gun->width)
	{
		ly = 0;
		while (ly++ < gun->height)
		{
			color = mlx_get_pixel(&gun->t.data, lx / gun->width * gun->t.width,
					ly / gun->height * gun->t.height);
			if (color != NOT_PIXEL)
			{
				col = ((g->img_w / 2.0) + lx - (gun->width / 2.0)) ;
				if (col >= 0 && col <= g->img_w && gun->ceil + ly >= 0 && gun->ceil
					+ ly <= g->img_h)
					my_mlx_pixel_put(img, col, gun->ceil + ly, color);
			}
		}
	}
}

void	render_gun(void *img, t_game *game)
{
	t_gun	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		gun->ceil = (game->img_h / 200.0) - 10;
		gun->height = (game->img_h - 2.0 * gun->ceil);
		gun->width = gun->height / (gun->t.height / gun->t.width);
		draw_gun(game, img, gun);
	}
	else
		printf("null\n");
	return;
}
