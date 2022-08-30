/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@guntudent.gun19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 00:05:32 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*mlx_get_pixel_pointer(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

static void	put_big_pixel(void *img, t_gun *gun, int color, int col, int ly)
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

static void	draw_gun(t_game *g, void *img, t_gun *gun)
{
	int		color;
	int		col;
	int		lx;
	int		ly;

	lx = 0;
	while (lx < gun->width)
	{
		ly = 0;
		while (ly < gun->height)
		{
			color = mlx_get_pixel(&gun->hold.data, lx / gun->width * gun->hold.width,
					ly / gun->height * gun->hold.height);
			if (color != NOT_PIXEL)
			{
				col = ((g->img_w / 2.0) + lx - (gun->width / 2.0)) ;
				if (col >= 0 && col <= g->img_w && gun->ceil + ly >= 0 && gun->ceil
					+ ly <= g->img_h)
					put_big_pixel(img, gun, color, col, ly);
			}
			ly += gun->pixel_size;
		}
		lx += gun->pixel_size;
	}
}

void	render_gun(void *img, t_game *game)
{
	t_gun	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		gun->ceil = (game->img_h / 200.0) - 10;
		gun->height = (game->img_h - 2.0 * gun->ceil);
		gun->width = gun->height / (gun->hold.height / gun->hold.width);
		gun->pixel_size = (int) gun->height / gun->hold.height;
		draw_gun(game, img, gun);
	}
	return ;
}
