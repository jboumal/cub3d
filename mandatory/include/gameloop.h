/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/20 00:07:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMELOOP_H
# define GAMELOOP_H

# include "cub3d.h"
# include "sys/time.h"

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

/*gameloop*/
int		game_loop(t_game *game);

/*update_cam*/
void	translate_cam(t_game *game);
void	rotate_cam(t_game *game);

#endif
