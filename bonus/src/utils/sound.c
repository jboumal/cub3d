/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:54:02 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/30 16:03:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_sound(char *path, t_game *g)
{
	char	*cmd_arg[3];

	cmd_arg[0] = SOUND_CMD;
	cmd_arg[1] = path;
	cmd_arg[2] = NULL;
	if (!fork())
	{
		execv(SOUND_PATH, cmd_arg);
		printf("command not found\n");
		quit(g);
	}
}
