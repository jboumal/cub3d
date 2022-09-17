/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_title.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:45:55 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/17 15:55:17 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TITLE_H
# define SCENE_TITLE_H

# include "cub3d.h"

typedef struct s_title
{
	int	index;
	t_img*	options_title;
	t_img*	new_game[2];
	t_img*	quit[2];
	t_img*	select_gun[2];
}	t_title;

#endif