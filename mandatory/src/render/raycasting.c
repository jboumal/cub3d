/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/13 21:55:50 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*get_wall_texture(int side)
{
	(void)side;
	return (NULL);
}

static void	draw_line(int x, double wall_dist, int side, t_data *img)
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
			my_mlx_pixel_put(img, x, y, 0x88 + 0x55 * side);
		y++;
	}
}

void	raycasting(int x, t_data *img, t_game *game)
{
	double		camera_x;
	t_vector	ray_dir;
	int			side;
	double		wall_dist;

	camera_x = 2 * x / (double) SCREEN_W - 1;
	ray_dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray_dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	side = 0;
	get_wall_texture(side);
	wall_dist = dda(ray_dir, &side, game);
	draw_line(x, wall_dist, side, img);
	if (x + 1 < SCREEN_W)
		raycasting(x + 1, img, game);
}
