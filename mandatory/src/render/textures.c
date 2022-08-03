/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:28:29 by jboumal           #+#    #+#             */
/*   Updated: 2022/08/03 08:35:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img = mlx_xpm_file_to_image(game->mlx, "img/wall1.xpm",
			&game->textures[N].width, &game->textures[N].height);
	game->textures[N].img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall2.xpm",
			&game->textures[E].width, &game->textures[E].height);
	game->textures[E].img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall3.xpm",
			&game->textures[S].width, &game->textures[S].height);
	game->textures[E].img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall4.xpm",
			&game->textures[W].width, &game->textures[W].height);
	game->textures[E].img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
}
