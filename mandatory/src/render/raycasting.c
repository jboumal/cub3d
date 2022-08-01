/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/01 19:35:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_start_end(int line_height, int *start, int *end)
{
	*start = -line_height / 2 + SCREEN_H / 2;
	*end = line_height / 2 + SCREEN_H / 2;
}

static int get_tex_x(t_ray *ray, t_game *g)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == W || ray->side == E)
		wall_x = g->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)g->textures.ea_wall.width);
	if((ray->side == W || ray->side == E)  && ray->dir.x > 0)
		tex_x = g->textures.ea_wall.width - tex_x - 1;
	if((ray->side == N || ray->side == S) && ray->dir.y < 0)
		tex_x = g->textures.no_wall.width - tex_x - 1;
	return (tex_x);
}

static void	draw_line(int x, t_ray *ray, t_data *img, t_game *g)
{
	int		color;
	int 	y;
	int 	text_y;
	int		line_height = SCREEN_H / ray->wall_dist;
	int		draw_start, draw_end;
	int		tex_x = get_tex_x(ray, g);

	set_start_end(line_height, &draw_start, &draw_end);
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < draw_start)
			my_mlx_pixel_put(img, x, y, 0x0087ceeb);
		else if (y > draw_end)
			my_mlx_pixel_put(img, x, y, 0xf5deb3);
		else
		{
			text_y = (y - draw_start) * g->textures.no_wall.height / (line_height);
			if (ray->side == N || ray->side == S)
				color = g->textures.no_wall.img[text_y * g->textures.no_wall.height + tex_x];
			else
				color = g->textures.ea_wall.img[text_y * g->textures.ea_wall.height + tex_x];
			my_mlx_pixel_put(img, x, y, color);
		}
		y++;
	}	
}

void	raycasting(int x, t_data *img, t_game *g)
{
	double		camera_x;
	t_ray		ray;

	camera_x = 2 * x / (double) SCREEN_W - 1;
	ray.dir.x = g->player.dir.x + g->player.plane.x * camera_x;
	ray.dir.y = g->player.dir.y + g->player.plane.y * camera_x;
	dda(&ray, g);
	draw_line(x, &ray, img, g);
	if (x + 1 < SCREEN_W)
		return (raycasting(x + 1, img, g));
}
