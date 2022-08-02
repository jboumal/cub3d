/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:28:29 by jboumal           #+#    #+#             */
/*   Updated: 2022/08/01 19:59:45 by vrogiste         ###   ########.fr       */
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
			&game->textures.no_wall.width, &game->textures.no_wall.height);
	game->textures.no_wall.img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall2.xpm",
			&game->textures.ea_wall.width, &game->textures.ea_wall.height);
	game->textures.ea_wall.img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall3.xpm",
			&game->textures.so_wall.width, &game->textures.so_wall.height);
	game->textures.ea_wall.img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
	img = mlx_xpm_file_to_image(game->mlx, "img/wall4.xpm",
			&game->textures.we_wall.width, &game->textures.we_wall.height);
	game->textures.ea_wall.img = (unsigned int *)
		mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian);
}
