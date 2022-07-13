/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:19:48 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/13 16:59:18 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"
# define TILEMAP_SIZE 12

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

void	render_minimap(t_game *game);

#endif