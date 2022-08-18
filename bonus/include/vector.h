/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:20:14 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/18 16:22:26 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/* vector */
t_vector	vector(double x, double y);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_scalar_multiplication(t_vector v, double a);
t_vector	vector_rotate(t_vector v, double a);
double		vector_norme(t_vector v);

#endif
