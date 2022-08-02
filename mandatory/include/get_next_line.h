/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:10:38 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/09 15:55:57 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

/*get_next_line_utils*/
int64_t	min(int64_t a, int64_t b);
size_t	str_len(char *str);
void	*ft_memchr(const void *s, int c, size_t n);
void	str_n_cpy(char *dst, char *src, size_t len);
char	*str_n_dup(char *src, size_t n);

/*get_next_line*/
char	*get_next_line(int fd);

#endif