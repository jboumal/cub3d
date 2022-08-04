/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:21 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 16:30:18 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/*put*/
void dputstr(int fd, char *s);

/* split */
char	**ft_split(char const *str, char c);

/* str */
size_t		str_len(const char *str);
int			str_n_cmp(const char *s1, const char *s2, size_t n);
bool		is_token(char *str, char *tokens, char sep, size_t n);

/* str_alloc */
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* str_arr */
void	str_arr_free(char **str);

/* utils */
int			ft_atoi(const char *str);

/* vector */
t_vector	vector(double x, double y);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_rotate(t_vector v, double a);


#endif
