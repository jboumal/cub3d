/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:05:15 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/29 11:27:01 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define NOT_PIXEL 9961608
# define MIN_SPRITE_DIST 0.7

/* sort sprite */
void	sort_sprite(t_game *g, t_sprite *obj, int i);

/* sprite */
void	render_sprites(void	*img, t_game *game);

#endif
