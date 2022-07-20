/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:22:37 by jboumal           #+#    #+#             */
/*   Updated: 2022/07/16 15:22:41 by jboumal          ###   ########.fr       */
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
	t_texture	wall;
	t_texture	wall2;
}	t_textures;

#endif
