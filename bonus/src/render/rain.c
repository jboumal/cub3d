/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:27 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/22 13:36:57 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raincasting(int x0, int x1, t_data *img, t_game *g)
{
	int			i;
	int			color;
	static int	offset_y;
	int			offset_x;

	offset_x = 1000 * g->player.pos.x
		+ 1000 * g->player.pos.y
		+ 1000 * g->player.dir.x
		+ 1000 * g->player.dir.y;
	i = 0;
	while (i < SCREEN_H)
	{
			color = mlx_get_pixel(
				&g->rain.data,
				((x0 + offset_x) % SCREEN_W) * ((double)g->rain.width / SCREEN_W),
				(((unsigned)(i - offset_y)) % SCREEN_H) * ((double)g->rain.height / SCREEN_H));
		if (get_r(color) > 40 && get_g(color) > 40 && get_b(color) > 40)
		{
			color |= 0x00FFFFFF;
			color = shade(color, mlx_get_pixel(img, x0, i), 0.3, 0.5);
			my_mlx_pixel_put(img, x0, i, color);
		}
		i++;
	}
	offset_y += 40;
	if (x0 < x1)
		return (raincasting(x0 + 1, x1, img, g));
}
