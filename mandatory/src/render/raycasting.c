/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/13 17:07:20 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*get_wall_texture(int side)
{
	(void)side;
	return (NULL);
}

static void	draw_line(int x, double wall_dist, int texture, t_data *img)
{
	(void)x;
	(void)wall_dist;
	(void)texture;
	(void)img;
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
	draw_line(x, side, wall_dist, img);
	if (x + 1 < SCREEN_W)
		raycasting(x + 1, img, game);
}
