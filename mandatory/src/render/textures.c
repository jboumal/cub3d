/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:28:29 by jboumal           #+#    #+#             */
/*   Updated: 2022/07/25 15:06:53 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img = mlx_xpm_file_to_image(game->mlx, "img/wall1.xpm", &game->textures.no_wall.width, &game->textures.no_wall.height);
	game->textures.no_wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
}
