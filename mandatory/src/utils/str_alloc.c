/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:23:40 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 15:25:02 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (str_len(src));
}

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = malloc(str_len(s) + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, str_len(s) + 1);
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	dst_len;

	if (!s)
		return (NULL);
	if (str_len(s) < start)
		return (ft_strdup(""));
	dst_len = str_len(s + start);
	if (len < dst_len)
		dst_len = len;
	dst = malloc(dst_len + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s + start, dst_len + 1);
	return (dst);
}