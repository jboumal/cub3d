/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:47:26 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/29 22:28:30 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	blt_dst(t_img *src, t_img *dst, t_vector d, t_rect r)
{
	int		x;
	int		y;
	char	*pixel_dst;
	char	*pixel_src;
	int		color;

	y = 0;
	while (y < r.height)
	{
		x = 0;
		while (x < r.width)
		{
			pixel_dst = dst->addr + ((y + (int) d.y) * dst->line_length
					+ (x + (int) d.x) * (dst->bits_per_pixel / 8));
			pixel_src = src->addr + ((y + r.y) * src->line_length + (x + r.x)
					* (src->bits_per_pixel / 8));
			color = (*(int *)pixel_src);
			if (color >= 0)
				*(unsigned int *) pixel_dst = *(unsigned int *) pixel_src;
			if (color > 0 && *(unsigned int *) pixel_dst == 0)
				*(unsigned int *) pixel_dst = 0xff000000;
			x++;
		}
		y++;
	}
}
