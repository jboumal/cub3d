/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/20 00:55:25 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_object_t(t_game *game, int index, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	img = mlx_xpm_file_to_image(game->mlx, path_to_texture, &game->
		list_object[index].obj_t.width, &game->list_object[index].obj_t.height);
	if (!img)
		parsing_error("error when loading object texture");
	game->list_object[index].obj_t.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->list_object[index].obj_t.allocated_img = img;
}

void	init_object(t_game *game)
{
	t_object	tree;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	tree.x = 3.5;
	tree.y = 7.5;
	tree.size = 0.5;
	game->list_object[0] = tree;
	load_object_t(game, 0, "img/object/tree.xpm");
}

static void	draw_object(t_game *game, void *img, t_object obj, double f_object_ceiling, double f_object_angle, double dist)
{
	int		lx;
	int		ly;
	double	f_object_height;
	double	f_object_width;
	int		color;
	int		n_object_column;

	f_object_height = (double) SCREEN_H - 2.0 * f_object_ceiling;
	f_object_width = f_object_height / ((double) obj.obj_t.height / (double) obj.obj_t.width);
	lx = 0;
	while (lx++ < f_object_width)
	{
		ly = 0;
		while (ly++ < f_object_height)
		{
			color = obj.obj_t.img[((int)(ly / f_object_height * obj.obj_t.height) * obj.obj_t.height + (int)(lx / f_object_width * obj.obj_t.width))];
			n_object_column = ((0.5 * (f_object_angle / (FOV / 2.0)) + 0.5) * (double) SCREEN_W + lx - (f_object_width / 2.0));
			if (n_object_column >= 0 && n_object_column < SCREEN_W)
			{
				if (color > 0 && game->depth_buffer[n_object_column] >= dist)
					my_mlx_pixel_put(img, n_object_column, (int) f_object_ceiling + ly, color);
			}
		}
	}
}

static void	init_draw_object(t_game *g, void *img, t_object obj, double f_obj_angle, double dist)
{
	double f_object_ceiling;

	f_object_ceiling = (((double) SCREEN_H / 2.0) - ((double) SCREEN_H / ((double) dist / obj.size)));
	draw_object(g, img, obj, f_object_ceiling, f_obj_angle, dist);
}

void	render_objects(void	*img, t_game *g)
{
	t_object	obj;
	int			i;
	double		fvec_x;
	double		fvec_y;
	double		f_obj_angle;

	i = 0;
	while (i < 1)
	{
		obj = g->list_object[i];
		fvec_x = obj.x - g->player.pos.x;
		fvec_y = obj.y - g->player.pos.y;
		f_obj_angle = atan2(fvec_x, fvec_y)
			- atan2(g->player.dir.x, g->player.dir.y);
		if (f_obj_angle < -M_PI)
			f_obj_angle += 2.0 * M_PI;
		if (f_obj_angle > M_PI)
			f_obj_angle -= 2.0 * M_PI;
		if (fabs(f_obj_angle) < FOV / 2.0 && sqrt(fvec_x * fvec_x + fvec_y * fvec_y) >= 1.0)
		{
			init_draw_object(g, img, obj, f_obj_angle,
				sqrt(fvec_x * fvec_x + fvec_y * fvec_y));
		}
		i++;
	}
}
