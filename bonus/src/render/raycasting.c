/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:39:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 14:51:43 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_start_end(int line_height, int *start, int *end)
{
	*start = -line_height / 2 + SCREEN_H / 2;
	*end = line_height / 2 + SCREEN_H / 2;
}

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

	tex_x = g->textures[g->map.data[ray->cell] - 1].width - tex_x - 1;
	return (tex_x);
}

static void	init_draw_line(t_draw_line_var *var, t_ray *ray, t_game *g)
{
	var->line_height = SCREEN_H / ray->wall_dist;
	set_start_end(var->line_height, &(var->draw_start), &(var->draw_end));
	var->tex_x = get_tex_x(ray, g);
	var->ray = ray;
}

static void	draw_line(int x, t_draw_line_var *var, t_data *img, t_game *g)
{
	int		y;
	int		tex_y;
	int		color;
	int		tex_h;

	y = 0;
	tex_h = g->textures[var->ray->side].height;
	while (y < SCREEN_H)
	{
		if (y >= var->draw_start && y <= var->draw_end)
		{
			tex_y = (y - var->draw_start) * tex_h / (var->line_height);
			color = g->textures[var->ray->side].img[tex_y * tex_h + var->tex_x];
			my_mlx_pixel_put(img, x, y, color);
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
	init_draw_line(&var, &ray, g);
	draw_line(x0, &var, img, g);
	if (x0 < x1)
		return (raycasting(x0 + 1, x1, img, g));
}
