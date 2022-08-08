/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:32:24 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/08 15:41:09 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(int y, t_vector floor_step, t_vector floor, t_data *img, t_game *g)
{
	for(int x = 0; x < SCREEN_W; ++x)
      {
        int cellX = floor.x;
        int cellY = floor.y;
        int tx = (int)(H * (floor.x - cellX)) & (H - 1);
        int ty = (int)(H * (floor.y - cellY)) & (H - 1);
        floor.x += floor_step.x;
        floor.y += floor_step.y;
        int color = g->textures[0].img[H * ty + tx];
        my_mlx_pixel_put(img, x, y, color);

      }
}

void	floorcasting(int y, t_data *img, t_game *g)
{
	t_player *p;
	t_vector ray_dir_0;
	t_vector ray_dir_1;
	double	 row_dist;
	t_vector floor_step;
	t_vector floor;
	
	p = &g->player;
	ray_dir_0 = vector(p->dir.x - p->plane.x, p->dir.y - p->plane.y);
	ray_dir_1 = vector(p->dir.x + p->plane.x, p->dir.y + p->plane.y);
	row_dist = (0.5 * SCREEN_H) / (y - SCREEN_H / 2);
	floor_step.x = row_dist * (ray_dir_1.x - ray_dir_0.x) / SCREEN_W;
	floor_step.y = row_dist * (ray_dir_1.y - ray_dir_0.y) / SCREEN_W;
	floor.x = p->pos.x + row_dist * ray_dir_0.x;
	floor.y = p->pos.y + row_dist * ray_dir_0.y;
	draw_line(y, floor_step, floor, img, g);
	if (y < SCREEN_H - 1)
		return (floorcasting(y + 1, img, g));
}