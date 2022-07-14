/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:27 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/14 10:30:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_down(int code, t_game *game)
{
	if (code == K_W)
		game->state.up = true;
	else if (code == K_S)
		game->state.down = true;
	else if (code == K_A)
		game->state.left = true;
	else if (code == K_D)
		game->state.right = true;
	return (0);
}

int	key_release(int code, t_game *game)
{
	if (code == K_W)
		game->state.up = false;
	else if (code == K_S)
		game->state.down = false;
	else if (code == K_A)
		game->state.left = false;
	else if (code == K_D)
		game->state.right = false;
	return (0);
}
