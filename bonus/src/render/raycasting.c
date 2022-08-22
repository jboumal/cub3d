/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 15:55:53 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tx(t_ray *ray, t_game *g)
{
	double	wall_x;
	int		tx;

	if (ray->side == W || ray->side == E)
		wall_x = g->player.pos.y + ray->dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->dist * ray->dir.x;
	wall_x -= floor((wall_x));
	if ((g->map.data[ray->cell] == 10))
		wall_x -= get_door(ray->cell, g)->ratio;
	tx = (int)(wall_x * (double)g->textures[g->map.data[ray->cell] - 1].width);
	if (g->map.data[ray->cell] != 10)
	{
		if ((ray->side == W || ray->side == E) && ray->dir.x > 0)
			tx = g->textures[g->map.data[ray->cell] - 1].width - tx - 1;
		if ((ray->side == N || ray->side == S) && ray->dir.y < 0)
			tx = g->textures[g->map.data[ray->cell] - 1].width - tx - 1;
	}
	return (tx);
}

static void	init_draw_line(
			t_draw_line_var *var,
			t_ray *ray,
			t_data *img,
			t_game *g)
{
	var->line_height = SCREEN_H / ray->dist;
	var->tx = get_tx(ray, g);
	var->draw_start = -var->line_height / 2 + SCREEN_H / 2;
	var->draw_end = var->line_height / 2 + SCREEN_H / 2;
	var->ray = ray;
}

static inline void	put_sky_reflect_px(
			int x,
			int y,
			t_draw_line_var *var,
			t_data *img)
{
	int	color;

	color = shade(
			mlx_get_pixel(img, x, y),
			mlx_get_pixel(img, x, SCREEN_H - 1 - y),
			0.8, 0.4);
	my_mlx_pixel_put(img, x, y, color);
}

static void	draw_line(int x, t_draw_line_var *var, t_data *img, t_game *g)
{
	int		y;
	int		ty;
	int		tex_h;
	int		color;

	y = 0;
	tex_h = g->textures[g->map.data[var->ray->cell] - 1].height;
	while (y < SCREEN_H)
	{
		if (y >= var->draw_start && y <= var->draw_end)
		{
			ty = (y - var->draw_start) * tex_h / (var->line_height);
			color = mlx_get_pixel(&g->textures[g->map.data[var->ray->cell] - 1].data, var->tx, ty);
			if (var->ray->side == N || var->ray->side == S)
				color = shade_color(color, 1.8);
			if (var->ray->side == E)
				color = shade_color(color, 1.2);
			my_mlx_pixel_put(img, x, y, color);
			if (y + var->line_height < SCREEN_H)
			{
				color = shade(mlx_get_pixel(img, x, y + var->line_height),
						color, 0.8, 0.6);
				my_mlx_pixel_put(img, x, y + var->line_height, color);
			}
		}
		else if (y > var->draw_end + var->line_height)
			put_sky_reflect_px(x, y, var, img);
		y++;
	}
}

void	raycasting(int x0, int x1, t_data *img, t_game *g)
{
	double			camera_x;
	t_ray			ray;
	t_draw_line_var	var;

	camera_x = 2 * x0 / (double) SCREEN_W - 1;
	ray.dir.x = g->player.dir.x + g->player.plane.x * camera_x;
	ray.dir.y = g->player.dir.y + g->player.plane.y * camera_x;
	dda(&ray, g);
	init_draw_line(&var, &ray, img, g);
	draw_line(x0, &var, img, g);
	g->depth_buf[x0] = ray.dist;
	if (x0 < x1)
		return (raycasting(x0 + 1, x1, img, g));
}
