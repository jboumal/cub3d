/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:33:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/14 09:46:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "cub3d.h"

# define K_PRESS_EVENT 2
# define K_RELEASE_EVENT 3
# define DESTROY_NOTIFY_EVENT 17

/*event*/
int	key_down(int code, t_game *game);
int	key_release(int code, t_game *game);

#endif
