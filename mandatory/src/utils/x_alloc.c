/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_alloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 23:40:13 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/04 23:44:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*x_malloc(size_t n)
{
	void	*p;

	p = malloc(n);
	if (!p)
	{
		dputstr(STDERR_FILENO, "failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	return (p);
}
