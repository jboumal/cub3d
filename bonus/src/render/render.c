/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/08 15:14:34 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render(t_game *game)
{
	t_data	img;

	img = get_new_img(game);
	floorcasting(0, &img, game);
	raycasting(0, &img, game);
	render_minimap(&img, game);
	mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
