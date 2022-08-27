/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:22:47 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/16 18:20:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

t_data	get_new_img(t_game *game)
{
	t_data	img;

	img.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(
			img.img,
			&img.bits_per_pixel,
			&img.line_length,
			&img.endian);
	return (img);
}

unsigned int	mlx_get_pixel(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	load_texture(void *mlx, char *path, t_texture *texture)
{
	texture->data.img = mlx_xpm_file_to_image(
			mlx,
			path,
			&texture->width,
			&texture->height);
	if (!texture->data.img)
		exit_error("error when loading texture");
	texture->data.addr = mlx_get_data_addr(
			texture->data.img,
			&texture->data.bits_per_pixel,
			&texture->data.line_length,
			&texture->data.endian);
}
