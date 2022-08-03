/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:14:20 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/03 08:51:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int64_t	min(int64_t a, int64_t b)
{
	return ((a <= b) * a + (b < a) * b);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n || !s)
		return (NULL);
	if (*((unsigned char *) s) == (unsigned char) c)
		return ((void *) s);
	return (ft_memchr(s + 1, c, n - 1));
}

void	str_n_cpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst && src)
	{
		while (src[i] && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

char	*str_n_dup(char *src, size_t n)
{
	char	*dst;

	dst = malloc((min(str_len(src), n) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	str_n_cpy(dst, src, n);
	return (dst);
}
