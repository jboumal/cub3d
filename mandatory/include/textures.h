/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:22:37 by jboumal           #+#    #+#             */
/*   Updated: 2022/07/25 15:45:00 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H
# include "cub3d.h"

typedef struct s_texture
{
	unsigned int	*img;
	int				width;
	int				height;
}	t_texture;

typedef struct s_textures
{
	t_texture	no_wall;
	t_texture	ea_wall;
	t_texture	we_wall;
	t_texture	so_wall;
}	t_textures;

#endif
