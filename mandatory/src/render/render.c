/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 17:05:32 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game)
{
	t_data	img;

	img = get_new_img(game);
	raycasting(0, &img, game);
	mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}

	// //
	// int map[] = {1,1,1,1,1,
	// 			1,0,0,0,1,
	// 			1,0,0,0,1,
	// 			1,0,0,0,1,
	// 			1,1,1,1,1};
	// game->map.data = map;
	// game->map.width = 5;
	// game->map.height = 5;
	// game->player.pos = vector(3, 3);
	// game->player.dir = vector(-1, 0);
	// game->player.plane = vector(0, 0.66);
	// //