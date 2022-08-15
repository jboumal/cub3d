/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/15 15:16:11 by vrogiste         ###   ########.fr       */
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
		arg->game = g;
		arg->i = i;
		arg->img = img;
		pthread_create(&th[i], NULL, routine, arg);
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
	t_data		img;

	img = get_new_img(game);
	compute_pixels(&img, game, routine1);
	compute_pixels(&img, game, routine2);
	render_minimap(&img, game);
	mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
