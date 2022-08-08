/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:32:24 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/08 16:50:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(int y, t_floor *floor, t_data *img, t_game *g)
{
	int	x;
	int	color;
	int	tx;
	int	ty;

	x = 0;
	while (x < SCREEN_W)
	{
		tx = (int)(H * (floor->column.x - (int)floor->column.x)) & (H - 1);
		ty = (int)(H * (floor->column.y - (int)floor->column.y)) & (H - 1);
		floor->column.x += floor->step.x;
		floor->column.y += floor->step.y;
		color = g->textures[0].img[H * ty + tx];
		my_mlx_pixel_put(img, x, y, color);
		x++;
	}
}

void	floorcasting(int y, t_data *img, t_game *g)
{
	t_vector	ray_dir_0;
	t_vector	ray_dir_1;
	double		row_dist;
	t_floor		floor;

	ray_dir_0 = vector_add(
			g->player.dir,
			vector_scalar_multiplication(g->player.plane, -1));
	ray_dir_1 = vector_add(g->player.dir, g->player.plane);
	row_dist = (0.5 * SCREEN_H) / (y - SCREEN_H / 2);
	floor.step.x = row_dist * (ray_dir_1.x - ray_dir_0.x) / SCREEN_W;
	floor.step.y = row_dist * (ray_dir_1.y - ray_dir_0.y) / SCREEN_W;
	floor.column.x = g->player.pos.x + row_dist * ray_dir_0.x;
	floor.column.y = g->player.pos.y + row_dist * ray_dir_0.y;
	draw_line(y, &floor, img, g);
	if (y < SCREEN_H - 1)
		return (floorcasting(y + 1, img, g));
}
