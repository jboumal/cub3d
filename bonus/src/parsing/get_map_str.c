/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:35:09 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/22 09:59:15 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_map_str(int fd)
{
	t_dy_str	dy_str;
	char		*line;
	char		*ptr;

	dy_str = dy_str_new();
	line = get_next_non_empty_line(fd);
	while (line)
	{
		ptr = line;
		while (*ptr)
		{
			if (*ptr != '\r')
				dy_str_append_c(&dy_str, *ptr);
			ptr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	while (ft_strchr(" \t\n\r", dy_str.str[dy_str.len - 1]))
		dy_str_pop_back(&dy_str);
	return (dy_str.str);
}
