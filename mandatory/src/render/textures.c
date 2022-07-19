/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:28:29 by jboumal           #+#    #+#             */
/*   Updated: 2022/07/16 15:28:30 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img = mlx_xpm_file_to_image(game->mlx, "img/wall1.xpm", &game->textures.wall.width, &game->textures.wall.height);
	game->textures.wall.img = (unsigned int *) mlx_get_data_addr (img, &bits_per_pixel, &size_line, &endian );
}
