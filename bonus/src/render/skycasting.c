/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:00:21 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/11 20:16:59 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_sky_texture(t_game *game)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, "img/sky.xpm",
			&game->sky.width, &game->sky.height);
	if (!img)
		parsing_error("error when loading door texture");
	game->sky.img = (unsigned int *) mlx_get_data_addr(img,
			&bits_per_pixel, &size_line, &endian);
}

double	get_angle(t_vector v1, t_vector v2)
{
	double	angle;

	angle = (atan2(v1.x, v1.y) - atan2(v2.x, v2.y));
	return (angle + 2 * M_PI * (angle < 0));
}

double	get_fov_ratio(t_game *g)
{
	return (atan(vector_norme(g->player.plane)) / M_PI);
}

void	skycasting(int x0, int x1, t_data *img, t_game *g)
{
	double	angle;
	int		tx;
	int		ty;
	int		ty_range;
	int		y;

	angle = get_angle(vector(0, 1), vector_add(
				g->player.dir,
				vector_scalar_multiplication(
					g->player.plane,
					(double)2 * x0 / (double)SCREEN_W - 1)));
	tx = angle / (2 * M_PI) * g->sky.width;
	ty_range = get_fov_ratio(g) * g->sky.width / SCREEN_W * (SCREEN_H / 2);
	y = 0;
	while (y < SCREEN_H / 2)
	{
		ty = y * (double)ty_range / (double)(SCREEN_H / 2);
		ty += (g->sky.height - ty_range) / 2;
		my_mlx_pixel_put(img, x0, y, g->sky.img[ty * g->sky.width + tx]);
		y++;
	}
	if (x0 < x1)
		return (skycasting(x0 + 1, x1, img, g));
}
