/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:45:55 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/28 22:07:06 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "cub3d.h"

# define BLACK 0x000000
# define BACKGROUND1 0x4F0C07
# define BACKGROUND2 0x880000

struct	s_game;

void	title_draw(struct s_game *game);

typedef struct s_title
{
	int		index;
	t_img	options;
	t_img	newgame[2];
	t_img	quit[2];
	t_img	select;
	t_img	render;
	t_img	hud;
}	t_title;

#endif