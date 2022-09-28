/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:10:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/28 22:55:21 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_background(t_img *img)
{
	int	i;
	int	j;

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
}

void	blt_dst(t_img *src, t_img *dst, int dx, int dy)
{
	int		x;
	int		y;
	char	*pixel_dst;
	char	*pixel_src;
	int		color;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			pixel_dst = dst->addr + ((y + dy) * dst->line_length + (x + dx)
					* (dst->bits_per_pixel / 8));
			pixel_src = src->addr + (y * src->line_length + x
					* (src->bits_per_pixel / 8));
			color = (*(int *)pixel_src);
			if (color >= 0)
				*(unsigned int *) pixel_dst = *(unsigned int *) pixel_src;
			if (color > 0 && *(unsigned int *) pixel_dst == 0)
				*(unsigned int *) pixel_dst = 0xff000000;
			x++;
		}
		y++;
	}
}

void	render_ui(t_img *img, t_game *game)
{
	render_background(img);
	blt_dst(&game->title.hud, img, SCREEN_W / 2 - game->title.hud.width / 2,
		SCREEN_H - UI_H);
	render_minimap(img, game);
}
