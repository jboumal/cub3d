/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/28 19:37:42 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define NOT_PIXEL 9961608

typedef struct s_sprite
{
	double		x;
	double		y;
	double		size;
	double		height;
	double		width;
	double		ceil;
	double		angle;
	double		dist_to_p;
	bool		is_collect;
	bool		is_in_fov;
	t_texture	t;
}	t_sprite;

/* sort sprite */
void	sort_sprite(t_game *g, t_sprite *obj, int i);

/* sprite */
void	render_sprites(void	*img, t_game *game);
