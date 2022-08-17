/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:27 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/05 09:29:24 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx, game->window);
	while (i < 4)
	{
		mlx_destroy_image(game->mlx, game->textures[i].allocated_img);
		i++;
	}
	free(game->map.data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_down(int code, t_game *game)
{
	if (code == K_W || code == K_UP)
		game->state.up = true;
	else if (code == K_S || code == K_DOWN)
		game->state.down = true;
	else if (code == K_A)
		game->state.left = true;
	else if (code == K_D)
		game->state.right = true;
	else if (code == K_LEFT)
		game->state.r_left = true;
	else if (code == K_RIGHT)
		game->state.r_right = true;
	else if (code == K_ESC)
		quit(game);
	return (0);
}

int	key_release(int code, t_game *game)
{
	if (code == K_W || code == K_UP)
		game->state.up = false;
	else if (code == K_S || code == K_DOWN)
		game->state.down = false;
	else if (code == K_A)
		game->state.left = false;
	else if (code == K_D)
		game->state.right = false;
	else if (code == K_LEFT)
		game->state.r_left = false;
	else if (code == K_RIGHT)
		game->state.r_right = false;
	return (0);
}

int	mouse_hook(int x, int y, t_game *game)
{
	(void) y;
	if (x < 400)
		game->state.m_left = 400 - x;
	else if (x > 400)
		game->state.m_right = x - 400;
	mouse_move(game, 500, 500);
	return (0);
}