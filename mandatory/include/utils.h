/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:32:21 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/01 16:46:15 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

/* vector */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

t_vector	vector(double x, double y);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_rotate(t_vector v, double a);

/* pair */
typedef struct s_pair
{
	int	x;
	int	y;
}	t_pair;

t_pair		pair(int x, int y);
size_t		ft_strlen(char *str);
int			ft_atoi(const char *str);

#endif
