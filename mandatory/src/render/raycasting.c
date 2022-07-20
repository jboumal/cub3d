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

static void	set_start_end(int line_height, int *start, int *end)
{
	*start = -line_height / 2 + SCREEN_H / 2;
	*end = line_height / 2 + SCREEN_H / 2;
}

static void	draw_line(int x, double wall_dist, t_face *face, t_data *img, t_game *g)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		text_x;
	int		text_y;
	int		color;
	int		y;
	static int print = true;

	if (x == 0)
		print = true;

	line_height = SCREEN_H / wall_dist;
	set_start_end(line_height, &draw_start, &draw_end);
	y = 0;
	text_x = 10;
	/* CRITICAL FOR PERFORMANCE */
	/* Avoid functions calls or heavy operation in loop */
	while (y < SCREEN_H)
	{
		if (y < draw_start)
			my_mlx_pixel_put(img, x, y, 0x0087ceeb);
		else if (y > draw_end)
			my_mlx_pixel_put(img, x, y, 0xf5deb3);
		else
		{
			text_y = (y - draw_start) * g->textures.wall.height / (line_height);
			if (face->side == N || face->side == S)
				color = g->textures.wall.img[text_y * g->textures.wall.height + text_x];
			else
				color = g->textures.wall2.img[text_y * g->textures.wall.height + text_x];
			my_mlx_pixel_put(img, x, y, color);
		}
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
	draw_line(x, wall_dist, &face, img, g);
	if (x + 1 < SCREEN_W)
		return (raycasting(x + 1, img, g));
}
