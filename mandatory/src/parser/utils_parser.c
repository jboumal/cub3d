/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:38:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/07/26 15:23:08 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *str)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	*skip_spaces(char *str)
{
	while (*str == ' ')
		(str++);
	return (str);
}

int	is_line_empty(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ')
		line++;
	return (*line == '\n' || *line == '\r');
}

char	*gnl_not_empty(int file_fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(file_fd);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\r')
	{
		free(line);
		return (gnl_not_empty(file_fd));
	}
	else
		return (line);
}
