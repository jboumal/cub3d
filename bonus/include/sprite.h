/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:09:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/20 15:26:54 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

typedef struct s_game	t_game;

typedef struct s_texture
{
	unsigned int	*img;
	int				width;
	int				height;
	void			*allocated_img;
}	t_texture;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		size;
	double		height;
	double		width;
	double		angle;
	double		ceil;
	double		dist_to_p;
	bool		is_in_fov;
	t_texture	t;
}	t_sprite;

void	init_sprite(t_game *game);
void	render_sprites(void	*img, t_game *game);

/* sort sprite */
void	sort_sprite(t_game *g, t_sprite *obj, int i);