/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 03:51:06 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/29 18:50:39 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_images(t_list lst, t_game *g)
{
	size_t		i;
	t_node		*node;
	t_img		*texture;

	i = 0;
	node = lst.head;
	while (i < clst_size(lst))
	{
		texture = node->content;
		if (texture)
			mlx_destroy_image(g->mlx, texture->img);
		node = node->next;
		i++;
	}
}

static void	free_sprites(t_game *g)
{
	int	i;

	i = 0;
	while (i < SPRITE_MAX)
	{
		if (g->list_sprite[i])
			mlx_destroy_image(g->mlx, g->list_sprite[i]->t.img);
		free(g->list_sprite[i]);
		i++;
	}
	i = 0;
	while (i < GUN_MAX)
	{
		if (g->list_gun[i])
			mlx_destroy_image(g->mlx, g->list_gun[i]->s.t.img);
		free(g->list_gun[i]);
		i++;
	}
}

int	quit(t_game *g)
{
	int	i;

	i = 0;
	while (i < WALL_MAX)
	{
		clear_images(g->walls[i].imgs, g);
		i++;
	}
	mlx_destroy_window(g->mlx, g->window);
	mlx_destroy_image(g->mlx, g->sky.img);
	mlx_destroy_image(g->mlx, g->floor.img);
	mlx_destroy_image(g->mlx, g->small_buffer.img);
	mlx_destroy_image(g->mlx, g->full_buffer.img);
	free(g->map.data);
	free(g->map.object_map);
	free(g->map.visible_tiles);
	free_sprites(g);
	lst_clear(&g->doors, free);
	exit(EXIT_SUCCESS);
	return (0);
}
