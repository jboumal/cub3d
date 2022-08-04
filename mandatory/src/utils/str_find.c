/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:46:13 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 22:08:19 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	if (*s)
		return (ft_strchr(s + 1, c));
	return (NULL);
}

char	*skip_spaces(char *s)
{
	if (s && ft_strchr(SPACES, *s))
		return (skip_spaces(s + 1));
	return (s);
}
