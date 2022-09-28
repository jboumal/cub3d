/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:10:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/28 21:39:19 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_background(t_img *img)
{
	int	i;
	int	j;
	int	border_width;

	border_width = 5;
	i = SCREEN_H - UI_H;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			if (i < SCREEN_H - UI_H + border_width)
				my_mlx_pixel_put(img, j, i, UI_COLOR1);
			else
				my_mlx_pixel_put(img, j, i, UI_COLOR2);
			j++;
		}
		i++;
	}
}

static void	render_frame(t_img *img)
{
	int	i;
	int	j;
	int	border_width;

	i = SCREEN_H - UI_H;
	border_width = 5;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < UI_H)
		{
			if (i < SCREEN_H - UI_H + border_width || j < border_width
				|| j > UI_H - border_width)
				my_mlx_pixel_put(img, j, i, 0x2d6e6f);
			j++;
		}
		i++;
	}
}

void	render_ui(t_img *img, t_game *game)
{
	render_background(img);
	render_minimap(img, game);
	render_frame(img);
}
