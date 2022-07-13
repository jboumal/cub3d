/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 13:33:11 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game)
{
	t_data	img;

	img = get_new_img(game);
	//
	my_mlx_pixel_put(&img, 5, 5, 0x00FFFFFF);
	//
	mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
