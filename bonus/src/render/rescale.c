/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:30:24 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/27 22:52:09 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*routine_rescale(void *arg)
{
	int			i;
	int			j;
	int			end;
	t_data		*new_img;
	t_data		*img;

	i = get_start(((t_th_arg *)arg)->i, 0, SCREEN_H - 1);
	end = get_end(((t_th_arg *)arg)->i, 0, SCREEN_H - 1);
	new_img = ((t_th_arg *)arg)->data[0];
	img = ((t_th_arg *)arg)->data[1];
	while (i <= end)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			my_mlx_pixel_put(
				new_img,
				j,
				i,
				mlx_get_pixel(img, j * SCALE, i * SCALE));
			j++;
		}
		i++;
	}
	return (arg);
}

t_data	rescale(t_data img, t_game *g)
{
	pthread_t	th[N_THREAD];
	t_data		new_img;
	int			i;
	t_th_arg	*arg;

	new_img = get_new_img(g->mlx, SCREEN_W, SCREEN_H);
	i = 0;
	while (i < N_THREAD)
	{
		arg = x_malloc(sizeof(t_th_arg));
		arg->i = i;
		arg->data[0] = &new_img;
		arg->data[1] = &img;
		if (pthread_create(&th[i], NULL, routine_rescale, arg))
			exit_error("unable to create thread");
		i++;
	}
	while (i)
	{
		pthread_join(th[i - 1], (void **)&arg);
		free(arg);
		i--;
	}
	mlx_destroy_image(g->mlx, img.img);
	return (new_img);
}
