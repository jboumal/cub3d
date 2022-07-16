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
	if (*start < 0)
		*start = 0;
	*end = line_height / 2 + SCREEN_H / 2;
	if (*end >= SCREEN_H)
		*end = SCREEN_H - 1;
}

static void	draw_pixel(t_data *img, t_point p, t_face face, double wall_dist, t_game *g)
{
	int		draw_start;
	int		draw_end;
	int		scaled_y;
	int		scaled_x;
	int		color;
	int		line_height;

	line_height = SCREEN_H / wall_dist;
	(void) face; 	(void) g;
	set_start_end(line_height, &draw_start, &draw_end);
	scaled_y = (int) (((double)(p.y - draw_start) / (double)(draw_end - draw_start)) * g->textures.wall.height);
	scaled_x = (int) (p.x / 3) % g->textures.wall.width;
	color = g->textures.wall.img[scaled_y * g->textures.wall.height + scaled_x];
	if (face.cell == 24 && (face.side == N || face.side == S))
		my_mlx_pixel_put(img, p.x, p.y, color);
	else
		my_mlx_pixel_put(img, p.x, p.y, 100);
}

static void	draw_line(int x, double wall_dist, t_face face, t_data *img, t_game *g)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_point	p;

	line_height = SCREEN_H / wall_dist;
	set_start_end(line_height, &draw_start, &draw_end);
	p = point(x, 0);
	while (p.y < SCREEN_H)
	{
		if (p.y < draw_start)
			my_mlx_pixel_put(img, p.x, p.y, 0);
		else if (p.y > draw_end)
			my_mlx_pixel_put(img, p.x, p.y, 0x00444444);
		else
			draw_pixel(img, p, face, wall_dist, g);
		p.y++;
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
	draw_line(x, wall_dist, face, img, g);
	if (x + 1 < SCREEN_W)
		return (raycasting(x + 1, img, g));
}
