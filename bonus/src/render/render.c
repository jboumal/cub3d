/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:06:51 by bel-mous          #+#    #+#             */
/*   Updated: 2022/08/11 23:17:49 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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

static void	*routine(void *arg)
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
	raycasting(start, end, ((t_th_arg *)arg)->img, g);
	return (arg);
}

static void	compute_pixels(t_data *img, t_game *g)
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
	compute_pixels(&img, game);
	render_minimap(&img, game);
	mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
