/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/20 20:05:21 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	compute_field_sprite(t_game *g)
{
	t_sprite	*obj;
	double		fvec_x;
	double		fvec_y;
	int			i;

	i = -1;
	while (i++ < 9)
	{
		obj = g->list_sprite[i];
		if (!obj)
			continue ;
		fvec_x = obj->x - g->player.pos.x;
		fvec_y = obj->y - g->player.pos.y;
		obj->dist_to_p = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);
		obj->angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		if (obj->angle < -M_PI)
			obj->angle += 2.0 * M_PI;
		if (obj->angle > M_PI)
			obj->angle -= 2.0 * M_PI;
		obj->is_in_fov = fabs(obj->angle) < FOV / 2.0 && obj->dist_to_p >= 1.0;
		if (i != 0 && obj->is_in_fov)
			sort_sprite(g, obj, i);
	}
}

static void	load_sprite_t(t_game *game, int index, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->list_sprite
		[index]->t.width, &game->list_sprite[index]->t.height);
	if (!img)
		parsing_error("error when loading sprite texture");
	game->list_sprite[index]->t.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->list_sprite[index]->t.allocated_img = img;
}

void	init_sprite(t_game *game)
{
	t_sprite	*obj;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	obj = malloc(sizeof(t_sprite));
	obj->x = 3.5;
	obj->y = 7.5;
	obj->size = 0.5;
	game->list_sprite[0] = obj;
	load_sprite_t(game, 0, "img/sprite/tree.xpm");

	obj = malloc(sizeof(t_sprite));
	obj->x = 2.5;
	obj->y = 6.5;
	obj->size = 0.5;
	game->list_sprite[1] = obj;
	load_sprite_t(game, 1, "img/sprite/tree.xpm");

	obj = malloc(sizeof(t_sprite));
	obj->x = 6.5;
	obj->y = 12.5;
	obj->size = 0.5;
	game->list_sprite[2] = obj;
	load_sprite_t(game, 2, "img/sprite/armor.xpm");

	obj = malloc(sizeof(t_sprite));
	obj->x = 29.5;
	obj->y = 2.5;
	obj->size = 0.4;
	game->list_sprite[3] = obj;
	load_sprite_t(game, 3, "img/sprite/barrel.xpm");

}

static void	draw_sprite(t_game *game, void *img, t_sprite obj)
{
	int		color;
	int		n_sprite_col;
	int		lx;
	int		ly;

	obj.ceil = ((SCREEN_H / 2.0) - (SCREEN_H / (obj.dist_to_p / obj.size)));
	obj.height = SCREEN_H - 2.0 * obj.ceil;
	obj.width = obj.height / (obj.t.height / obj.t.width);

	// pb : toujours au centre de l'image (mais bonne taille)
	lx = 0;
	while (lx++ < obj.width)
	{
		ly = 0;
		while (ly++ < obj.height)
		{
			color = obj.t.img[(int)(ly / obj.height * obj.t.height)
				*obj.t.width + (int)(lx / obj.width * obj.t.width)];
			n_sprite_col = ((0.5 * (obj.angle / (FOV / 2.0)) + 0.5)
					* SCREEN_W + lx - (obj.width / 2.0));
			if (n_sprite_col >= 0 && n_sprite_col < SCREEN_W)
			{
				if (color > 0 && game->depth_buf[n_sprite_col] >= obj.dist_to_p)
					my_mlx_pixel_put(img, n_sprite_col, obj.ceil + ly, color);
			}
		}
	}
}

void	render_sprites(void	*img, t_game *g)
{
	t_sprite	*obj;
	int			i;

	compute_field_sprite(g);
	i = -1;
	while (i++ < 9)
	{
		obj = g->list_sprite[i];
		if (obj && obj->is_in_fov)
			draw_sprite(g, img, *obj);
	}
}
