/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:33:01 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/04 18:25:48 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_gun_anim_texture(t_game *game, t_sprite *gun, int index, char *gun_name)
{
	int		i;
	char	*path;
	char	*path_2;
	char	xpm_path[6];

	i = 0;
	ft_strncpy(xpm_path, EXTENSION, 5);
	while (i <= 4)
	{
		path = strjoin(GUN_PATH, gun_name);
		xpm_path[0] = i + 48;
		path_2 = strjoin(path, xpm_path);
		if (i == 0)
		{
			load_texture(game->mlx, path_2, &gun->t);
			bound_start(gun, gun->t);
		}
		else
		{
			load_texture(game->mlx, path_2, &gun->anim[i]);
			bound_start(gun, gun->anim[i]);
		}
		game->list_gun[index] = gun;
		free(path_2);
		free(path);
		i++;
	}
}

void	init_gun(t_game *game)
{
	t_sprite	*gun;
	int		i;

	i = 0;
	while (i <= 3)
	{
		gun = x_malloc(sizeof(t_sprite));
		gun->dist_to_p = 0;
		gun->angle = 0;
		gun->x_end = 0;
		gun->y_end = 0;
		if (i == 0)
		{
			init_gun_anim_texture(game, gun , i, "pistol");
			game->list_active_gun[0] = gun;
		}
		else if (i == 1)
			init_gun_anim_texture(game, gun , i, "mach");
		else if (i == 2)
			init_gun_anim_texture(game, gun , i, "sulf");
		else if (i == 3)
			init_gun_anim_texture(game, gun , i, "knife");
		i++;
	}
}

void	render_gun(void *img, t_game *game)
{
	t_sprite	*gun;

	gun = game->list_active_gun[game->active_gun];
	if (gun)
	{
		gun->ceil = game->img_h / 6.0;
		gun->height = game->img_h - gun->ceil;
		gun->width = gun->height / (gun->t.height / gun->t.width);
		gun->pixel_size = (int) gun->height / gun->t.height;
		draw_sprite(game, img, gun, &gun->t);
	}
}
