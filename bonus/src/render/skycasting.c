/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:00:21 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 13:15:31 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	tx = 4 * angle / (2 * M_PI) * g->sky.width;
	ty_range = 4 * get_fov_ratio(g) * g->sky.width / SCREEN_W * (SCREEN_H / 2);
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
