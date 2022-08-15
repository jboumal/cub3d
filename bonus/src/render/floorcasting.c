/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:32:24 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/15 15:00:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_floor_texture(t_game *game)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, "img/floor2.xpm",
			&game->floor.width, &game->floor.height);
	if (!img)
		exit_error("error when loading door texture");
	game->floor.img = (unsigned int *) mlx_get_data_addr(img,
			&bits_per_pixel, &size_line, &endian);
}

static void	draw_line(int y, t_scanline *scanline, t_data *img, t_game *g)
{
	int	x;
	int	color;
	int	tx;
	int	ty;
	int	h;

	x = 0;
	h = g->floor.height;
	while (x < SCREEN_W)
	{
		tx = (int)(h * (scanline->floor.x - (int)scanline->floor.x)) & (h - 1);
		ty = (int)(h * (scanline->floor.y - (int)scanline->floor.y)) & (h - 1);
		scanline->floor.x += scanline->step.x;
		scanline->floor.y += scanline->step.y;
		color = g->floor.img[h * ty + tx];
		my_mlx_pixel_put(img, x, y, color);
		x++;
	}
}

void	floorcasting(int y0, int y1, t_data *img, t_game *g)
{
	t_vector	ray_dir_0;
	t_vector	ray_dir_1;
	double		row_dist;
	t_scanline	scanline;

	ray_dir_0 = vector_add(
			g->player.dir,
			vector_scalar_multiplication(g->player.plane, -1));
	ray_dir_1 = vector_add(g->player.dir, g->player.plane);
	row_dist = (0.5 * SCREEN_H) / (y0 - SCREEN_H / 2);
	scanline.step.x = row_dist * (ray_dir_1.x - ray_dir_0.x) / SCREEN_W;
	scanline.step.y = row_dist * (ray_dir_1.y - ray_dir_0.y) / SCREEN_W;
	scanline.floor.x = g->player.pos.x + row_dist * ray_dir_0.x;
	scanline.floor.y = g->player.pos.y + row_dist * ray_dir_0.y;
	draw_line(y0, &scanline, img, g);
	if (y0 < y1)
		return (floorcasting(y0 + 1, y1, img, g));
}
