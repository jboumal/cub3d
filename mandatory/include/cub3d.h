/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:12 by bel-mous          #+#    #+#             */
/*   Updated: 2022/07/25 15:09:15 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
//# include <../mlx/mlx.h>
# include <../mlx_linux/mlx.h>
# include <stdio.h>

# include <stdlib.h>
# include <math.h>
# include <get_next_line.h>
# include <limits.h>

# include "utils.h"
# include "parser.h"
# include "gameloop.h"
# include "event.h"
# include "render.h"

# define SCREEN_W 1920
# define SCREEN_H 1080
# define SCREEN_TITLE "cub3d"

#endif
