/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:12 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/04 17:02:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <get_next_line.h>
# include <limits.h>
# include <string.h>

# include "utils.h"
# include "data_struct.h"
# include "parser.h"
# include "gameloop.h"
# include "event.h"
# include "render.h"

# define SCREEN_W 1280
# define SCREEN_H 720
# define SCREEN_TITLE "cub3d"

#endif
