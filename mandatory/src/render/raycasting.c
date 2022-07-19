/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/20 00:08:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_wall_offset(double wall_dist, t_vector *player_pos, double y)
{
	printf(", y %f\n", player_pos->y);
	return (sqrt(wall_dist * wall_dist - (y - player_pos->y) * (y - player_pos->y)) + player_pos->x);
}

static void	set_start_end(int line_height, int *start, int *end)
{
	*start = -line_height / 2 + SCREEN_H / 2;
	if (*start < 0)
		*start = 0;
	*end = line_height / 2 + SCREEN_H / 2;
	if (*end >= SCREEN_H)
		*end = SCREEN_H - 1;
}

static void	draw_line(int x, double wall_dist, t_face *face, t_data *img, t_game *g)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		scaled_x;
	int		scaled_y;
	int		color;
	int		y;

	line_height = SCREEN_H / wall_dist;
	set_start_end(line_height, &draw_start, &draw_end);
	y = 0;
	scaled_x = 0x00888888;
	//scaled_x = (int) (get_wall_offset(wall_dist, &(g->player.pos), face->cell % g->map.width) * g->textures.wall.width);
	if (face->cell == 24 && face->side == N)
		printf(", printx: %d, offset %f, ", scaled_x, get_wall_offset(wall_dist, &(g->player.pos), face->cell % g->map.width));
	/* CRITICAL FOR PERFORNANCE */
	/* Avoid functions calls or heavy operation in loop */
	while (y < SCREEN_H)
	{
		if (y < draw_start)
			my_mlx_pixel_put(img, x, y, 0);
		else if (y > draw_end)
			my_mlx_pixel_put(img, x, y, 0x00444444);
		else
		{
			scaled_y = (y - draw_start) * g->textures.wall.height / (line_height);
			color = g->textures.wall.img[scaled_y * g->textures.wall.height + scaled_x];
			if (face->cell == 24 && (face->side == N || face->side == S))
				my_mlx_pixel_put(img, x, y, color);
			else
				my_mlx_pixel_put(img, x, y, 100);
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
	if (face.cell == 24 && face.side == N)
		printf("DIST: %f, cell %d", wall_dist, face.cell);
	draw_line(x, wall_dist, &face, img, g);
	if (x + 1 < SCREEN_W)
		return (raycasting(x + 1, img, g));
}
