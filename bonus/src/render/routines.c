/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:39:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/12 00:41:47 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_start(int i, int start, int end)
{
	return (i * ((end - start) / N_THREAD) + start);
}

static int	get_end(int i, int start, int end)
{
	int	res;

	res = (i + 1) * ((end - start) / N_THREAD) + start - 1;
	if (end - res <= (end - start) / N_THREAD)
		res += end - res;
	return (res);
}

void	*routine1(void *arg)
{
	t_game	*g;
	int		i;
	int		start;
	int		end;

	g = ((t_th_arg *)arg)->game;
	i = ((t_th_arg *)arg)->i;
	start = get_start(i, SCREEN_H / 2, SCREEN_H - 1);
	end = get_end(i, SCREEN_H / 2, SCREEN_H - 1);
	floorcasting(start, end, ((t_th_arg *)arg)->img, g);
	start = get_start(i, 0, SCREEN_W - 1);
	end = get_end(i, 0, SCREEN_W - 1);
	skycasting(start, end, ((t_th_arg *)arg)->img, g);
	return (arg);
}

void	*routine2(void *arg)
{
	t_game	*g;
	int		i;
	int		start;
	int		end;

	g = ((t_th_arg *)arg)->game;
	i = ((t_th_arg *)arg)->i;
	start = get_start(i, 0, SCREEN_W - 1);
	end = get_end(i, 0, SCREEN_W - 1);
	raycasting(start, end, ((t_th_arg *)arg)->img, g);
	return (arg);
}
