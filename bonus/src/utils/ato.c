/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:39:28 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/17 15:58:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	atoui8_error(const char *s, uint8_t *n)
{
	int			sum;

	sum = 0;
	while (ft_strchr(SPACES, *s))
		s++;
	while (*s >= '0' && *s <= '9')
	{
		sum *= 10;
		sum += *s - '0';
		if (sum > 255)
			return (true);
		s++;
	}
	if (n)
		*n = sum;
	return (!ft_strchr(" \t\n\r\v\f", *s) && *s);
}

int	isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
