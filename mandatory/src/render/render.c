/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 18:06:43 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	render_minimap(game);
}
