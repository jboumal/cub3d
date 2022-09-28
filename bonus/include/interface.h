/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:12:24 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/28 21:42:25 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "cub3d.h"

# define TILEMAP_SIZE 12
# define UI_H 150
# define UI_COLOR1 0x2d6e6f
# define UI_COLOR2 0x173f3f
# define MMAP_COLOR1 0x4B7A68
# define MMAP_COLOR2 0x7CE7D6

void	render_ui(t_img *img, t_game *game);

#endif