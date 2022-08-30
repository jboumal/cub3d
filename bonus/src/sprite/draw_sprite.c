/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:48:56 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 14:57:20 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprite(t_game *g, t_sprite *obj, int i)
{
	t_sprite	*sprite;
	int			j;

	while (i >= 1 && obj->dist_to_p > g->list_sprite[i - 1]->dist_to_p)
	{
		sprite = g->list_sprite[i];
		g->list_sprite[i] = g->list_sprite[i - 1];
		g->list_sprite[i - 1] = sprite;
		i--;
	}
}

void	compute_field_sprite(t_game *g)
{
	t_sprite	*obj;
	double		fvec_x;
	double		fvec_y;
	int			i;

	i = -1;
	while (i++ < SPRITE_MAX - 1)
	{
		obj = g->list_sprite[i];
		if (!obj)
			continue ;
		fvec_x = obj->x - g->player.pos.x;
		fvec_y = obj->y - g->player.pos.y;
		obj->dist_to_p = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);
		obj->angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		if (obj->angle < -M_PI)
			obj->angle += 2.0 * M_PI;
		if (obj->angle > M_PI)
			obj->angle -= 2.0 * M_PI;
		obj->is_in_fov = fabs(obj->angle) < (g->player.fov / 2.0);
		if (i != 0)
			sort_sprite(g, obj, i);
	}
}

void	put_big_pixel(void *img, t_gun *gun, int color, int col, int ly)
{
	int	i;
	int	j;

	i = 0;
	while (i < gun->pixel_size)
	{
		j = 0;
		while (j < gun->pixel_size)
		{
			my_mlx_pixel_put(img, col + i, gun->ceil + ly + j, color);
			j++;
		}
		i++;
	}
}

void	put_big_pixel_s(void *img, t_game *g, t_sprite *s, int color, int col, int ly)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->pixel_size)
	{
		j = 0;
		while (j < s->pixel_size)
		{
			if (g->depth_buf[col] >= s->dist_to_p)
				my_mlx_pixel_put(img, col + i, s->ceil + ly + j, color);
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_game *g, void *img, t_sprite *s)
{
	int		color;
	int		col;
	int		lx;
	int		ly;

	//lx = s->width * s->x_start;
	lx = 0;
	while (lx < s->width)
	{
		//ly = s->height * s->y_start;
		ly = 0;
		while (ly < s->height)
		{
			color = mlx_get_pixel(&s->t.data, lx / s->width * s->t.width,
					ly / s->height * s->t.height);
			if (color != NOT_PIXEL)
			{
				col = (0.5 * (s->angle / (g->player.fov / 2.0)) + 0.5)
					* g->img_w + lx - (s->width / 2.0);
				if (col >= 0 && col <= g->img_w && s->ceil + ly >= 0 && s->ceil
					+ ly <= g->img_h)
					//my_mlx_pixel_put(img, col, s->ceil + ly, color);
					put_big_pixel_s(img, g, s, color, col, ly);
			}
			ly += s->pixel_size;
		}
		lx += s->pixel_size;
	}
}
