/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:19:13 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/30 02:13:08 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_gun
{
	double		height;
	double		width;
	double		ceil;
	t_texture	hold;
}	t_gun;

void	render_gun(void *img, t_game *game);
