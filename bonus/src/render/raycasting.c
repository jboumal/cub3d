/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/15 20:03:39 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tex_x(t_ray *ray, t_game *g)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == W || ray->side == E)
		wall_x = g->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)g->textures[E].width);
	if ((ray->side == W || ray->side == E) && ray->dir.x > 0)
		tex_x = g->textures[E].width - tex_x - 1;
	if ((ray->side == N || ray->side == S) && ray->dir.y < 0)
		tex_x = g->textures[N].width - tex_x - 1;
	return (tex_x);
}

static void	init_draw_line(
			t_draw_line_var *var,
			t_ray *ray,
			t_data *img,
			t_game *g)
{
	var->line_height = SCREEN_H / ray->wall_dist;
	var->draw_start = -var->line_height / 2 + SCREEN_H / 2;
	var->draw_end = var->line_height / 2 + SCREEN_H / 2;
	var->tex_x = get_tex_x(ray, g);
	var->ray = ray;
	var->arr = (unsigned int *)mlx_get_data_addr(
			img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
}

static void	draw_line(int x, t_draw_line_var *var, t_data *img, t_game *g)
{
	int		y;
	int		tex_y;
	int		tex_h;
	int		color;

	y = 0;
	tex_h = g->textures[var->ray->side].height;
	while (y < SCREEN_H)
	{
		if (y >= var->draw_start && y <= var->draw_end)
		{
			tex_y = (y - var->draw_start) * tex_h / (var->line_height);
			color = g->textures[var->ray->side].img[tex_y * tex_h + var->tex_x];
			my_mlx_pixel_put(img, x, y, color);
			if (y + var->line_height < SCREEN_H)
			{
				color = shade(
						var->arr[(y + var->line_height) * SCREEN_W + x],
						color, 0.8, 0.6);
				my_mlx_pixel_put(img, x, y + var->line_height, color);
			}
		}
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
	if (x0 < x1)
		return (raycasting(x0 + 1, x1, img, g));
}
