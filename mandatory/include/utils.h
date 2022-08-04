/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:21 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 23:42:27 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

# define BUFFER_SIZE 1024

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/* get_next_line */
char		*get_next_line(int fd);

/*get_first_non_empty_line */
char		*get_first_non_empty_line(int fd);

/* min_max */
int64_t		min(int64_t a, int64_t b);
int64_t		max(int64_t a, int64_t b);

/*put*/
void		dputstr(int fd, char *s);

/* split */
char		**ft_split(char const *str, char c);

/* str */
size_t		str_len(const char *str);
int			str_n_cmp(const char *s1, const char *s2, size_t n);
bool		is_token(char *str, char *tokens, char sep, size_t n);

/* str_alloc */
char		*ft_strdup(const char *s);
char		*str_n_dup(char *src, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* str_arr */
void		str_arr_free(char **str);

/* str_copy */
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		str_n_cpy(char *dst, char *src, size_t len);

/* str_find */
char		*ft_strchr(const char *s, int c);
char		*skip_spaces(char *s);

/* utils */
int			ft_atoi(const char *str);

/* vector */
t_vector	vector(double x, double y);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_rotate(t_vector v, double a);

/* x_alloc */
void		*x_malloc(size_t n);

#endif
