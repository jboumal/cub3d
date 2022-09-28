/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:19:22 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/28 17:41:13 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vector_norme(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_vector	vector_normalize(t_vector v)
{
	return (vector(v.x / vector_norme(v), v.y / vector_norme(v)));
}
