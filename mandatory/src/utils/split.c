/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:21:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 15:22:20 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*start(char *s, char c)
{
	if (!*s || *s != c)
		return (s);
	return (start(s + 1, c));
}

static char	*end(char *s, char c)
{
	if (!*s)
		return (s);
	if (*s == c)
		return (end(s + 1, c));
	while (*s && *s != c)
		s++;
	return (s);
}

static size_t	count_words(char *s, char c)
{
	if (*start(s, c))
		return (1 + count_words(end(s, c), c));
	return (0);
}

static char	**error(char **dst)
{
	char	**ptr;

	ptr = dst;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(dst);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**dst;
	char	**ptr;
	char	*s;

	s = (char *)str;
	dst = malloc(sizeof(char *) * (1 + count_words(s, c)));
	if (!dst)
		return (NULL);
	ptr = dst;
	while (*start(s, c))
	{
		*ptr = ft_substr(start(s, c), 0, end(s, c) - start(s, c));
		if (!*ptr)
			return (error(dst));
		ptr++;
		s = end(s, c);
	}
	*ptr = NULL;
	return (dst);
}