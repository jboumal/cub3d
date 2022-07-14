/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 14:31:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMELOOP_H
# define GAMELOOP_H

# include "cub3d.h"

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

/*gameloop*/
int		game_loop(t_game *game);

/*update_cam*/
void	translate_cam(t_game *g);
void	rotate_cam(t_game *g);

#endif
