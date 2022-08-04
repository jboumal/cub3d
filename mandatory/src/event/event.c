/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:27 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/05 00:07:51 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	quit_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(game->mlx, game->textures[i].allocated_img);
		i++;
	}
	free(game->map.data);
	exit(EXIT_SUCCESS);
}

int	key_down(int code, t_game *game)
{
	printf("%d\n", code);
	if (code == K_W)
		game->state.up = true;
	else if (code == K_S)
		game->state.down = true;
	else if (code == K_A)
		game->state.left = true;
	else if (code == K_D)
		game->state.right = true;
	else if (code == K_ESC)
		quit_game(game);
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
