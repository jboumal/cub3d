/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/16 19:44:58 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	compute_pixels(t_data *img, t_game *g, void *(*routine)(void *))
{
	pthread_t	th[N_THREAD];
	int			i;
	t_th_arg	*arg;

	i = 0;
	while (i < N_THREAD)
	{
		arg = x_malloc(sizeof(t_th_arg));
		arg->i = i;
		arg->data[0] = img;
		arg->data[1] = g;
		if (pthread_create(&th[i], NULL, routine, arg))
			exit_error("unable to create thread");
		i++;
	}
	i = 0;
	while (i < N_THREAD)
	{
		pthread_join(th[i], (void **)&arg);
		free(arg);
		i++;
	}
}

void	render(t_game *game)
{
	t_data	*img;

	img = &game->small_buffer;
	compute_pixels(img, game, routine_floor);
	compute_pixels(img, game, routine_sky);
	compute_pixels(img, game, routine_wall);
	render_sprites(img, game);
	if (SCALE != 1)
	{
		compute_pixels(img, game, routine_rescale);
		img = &game->full_buffer;
	}
	render_minimap(img, game);
	mlx_put_image_to_window(game->mlx, game->window, img->img, 0, 0);
}
