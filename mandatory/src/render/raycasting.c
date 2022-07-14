/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 14:28:43 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(int x, double wall_dist, t_face face, t_data *img)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	line_height = SCREEN_H / wall_dist;
	draw_start = -line_height / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_H / 2;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < draw_start)
			my_mlx_pixel_put(img, x, y, 0);
		else if (y > draw_end)
			my_mlx_pixel_put(img, x, y, 0x00444444);
		else
			my_mlx_pixel_put(img, x, y, 0x88 + 0x55 * (face.side % 2));
		y++;
	}
}

void	raycasting(int x, t_data *img, t_game *g)
{
	double		camera_x;
	t_vector	ray_dir;
	t_face		face;
	double		wall_dist;

	camera_x = 2 * x / (double) SCREEN_W - 1;
	ray_dir.x = g->player.dir.x + g->player.plane.x * camera_x;
	ray_dir.y = g->player.dir.y + g->player.plane.y * camera_x;
	wall_dist = dda(ray_dir, &face, g);
	draw_line(x, wall_dist, face, img);
	if (x + 1 < SCREEN_W)
		return (raycasting(x + 1, img, g));
}
