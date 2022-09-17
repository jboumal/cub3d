/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:44 by bel-mous          #+#    #+#             */
/*   Updated: 2022/09/17 16:11:16 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_index(int code, t_game *game)
{
	if (code == K_W || code == K_UP)
		game->index = (game->index + 1) % 2;
	else if (code == K_S || code == K_DOWN)
		game->index = (game->index - 1);
	else if (code == 36 || code == 49)
	{
		if (game->index == 0)
		{
			mlx_hook(game->window, K_PRESS_EVENT, K_PRESS_EVENT, key_down, game);
			game->scene = GAME;
		} else {
			quit(game);
		}
		
	}
	if (game->index < 0)
		game->index = 1;
	return (0);
}

void	initialize_texture(t_game *g)
{
	g->options = get_img_from_xpm(g->mlx, "img/title/options.xpm");
	g->newgame1 = get_img_from_xpm(g->mlx, "img/title/newgame1.xpm");
	g->newgame2 = get_img_from_xpm(g->mlx, "img/title/newgame2.xpm");
	g->select1 = get_img_from_xpm(g->mlx, "img/title/select1.xpm");
	g->quit1 = get_img_from_xpm(g->mlx, "img/title/quit1.xpm");
	g->quit2 = get_img_from_xpm(g->mlx, "img/title/quit2.xpm");
	mlx_hook(g->window, K_PRESS_EVENT, K_PRESS_EVENT, move_index, g);
}

void title_update(t_game *game)
{
	static int test = 0;
	if (test == 0)
	{
		mlx_hook(game->window, K_PRESS_EVENT, K_PRESS_EVENT, key_down, game);
		initialize_texture(game);
		t_img img = get_new_img(game->mlx, SCREEN_W, SCREEN_H);
		int	i;
		int	j;

		i = 0;
		while (i < SCREEN_H)
		{
			j = 0;
			while (j < SCREEN_W)
			{
				if ((i >= SCREEN_H / 2 - 300 + 20 && i <= SCREEN_H / 2 - 300 + 63) || i == SCREEN_H / 2 - 300 + 66 || i == SCREEN_H / 2 - 300 + 67)
				{
					//my_mlx_pixel_put(&img, j, i, 0x000000);
				}
				else if ((i >= SCREEN_H / 2 - 190 && i <= SCREEN_H / 2 + 190) && j > SCREEN_W / 2 - 300 && j < SCREEN_W / 2 + 300)
				{
					my_mlx_pixel_put(&img, j, i, 0x4F0C07);
				}
				else
				{
					my_mlx_pixel_put(&img, j, i, 0x880000);
				}
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(game->mlx, game->window, img.img, 0, 0);
		mlx_put_image_to_window(game->mlx, game->window, game->options.img, SCREEN_W / 2 - game->options.width / 2, SCREEN_H / 2 - 300);
		if (game->index != 0)
			mlx_put_image_to_window(game->mlx, game->window, game->newgame1.img, SCREEN_W / 2 - game->newgame1.width / 2 - 30, SCREEN_H / 2 - 190);
		else
			mlx_put_image_to_window(game->mlx, game->window, game->newgame2.img, SCREEN_W / 2 - game->newgame2.width / 2 - 30, SCREEN_H / 2 - 190);
		if (game->index != 1)
			mlx_put_image_to_window(game->mlx, game->window, game->quit1.img, SCREEN_W / 2 - game->quit1.width / 2 - 30, SCREEN_H / 2 - 190 + 50);
		else
			mlx_put_image_to_window(game->mlx, game->window, game->quit2.img, SCREEN_W / 2 - game->quit2.width / 2 - 30, SCREEN_H / 2 - 190 + 50);
		mlx_put_image_to_window(game->mlx, game->window, game->select1.img, SCREEN_W / 2 - game->select1.width / 2 - 250, SCREEN_H / 2 - 190 + game->index * 45);
		//mlx_string_put(game->mlx, game->window, SCREEN_W / 2, SCREEN_H / 2, 0xffffff, "New Game");
	}
	test = 0;
}
