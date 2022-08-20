/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:50:28 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/20 14:24:52 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


static void	create_sprite(t_game *game)
{
	;
}

void	parse_sprite(t_game *game, int fd)
{
	char	*line;

	line = get_next_non_empty_line(fd);
	while (line)
	{
		;
	}
}
