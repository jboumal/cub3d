/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:38:25 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/04 16:13:47 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *str, char *line)
{
	free(line);
	write(2, "Error\n", str_len("Error\n"));
	write(2, str, str_len(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
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

char	*gnl_not_empty(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\r')
	{
		free(line);
		return (gnl_not_empty(fd));
	}
	else
		return (line);
}
