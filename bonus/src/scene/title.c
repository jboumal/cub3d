/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:44 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/12 17:54:25 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void title_update(t_game *game)
{
	static int test = 0;
	if (test == 0)
	{
		t_img img = get_new_img(game->mlx, SCREEN_W, SCREEN_H);
		int	i;
		int	j;

		i = 0;
		while (i < SCREEN_H)
		{
			j = 0;
			while (j < SCREEN_W)
			{
				my_mlx_pixel_put(&img, j, i, 0x7c160e);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
		mlx_string_put(game->mlx, game->window, SCREEN_W / 2, SCREEN_H / 2, 0xffffff, "New Game");
	}
	test = 1;
}
