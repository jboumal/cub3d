/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:54:02 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/29 15:57:08 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_sound(char *path)
{
	char	*str;

	if (!fork())
	{
		str = strjoin("afplay sounds/", path);
		system(str);
		free(str);
		exit(1);
	}
}
