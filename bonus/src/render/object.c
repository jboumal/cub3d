/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/19 17:20:06 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_object_t(t_game *game, int index, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	img = mlx_xpm_file_to_image(game->mlx, path_to_texture,
			&game->list_object[index].obj.width, &game->list_object[index].obj.height);
	if (!img)
		parsing_error("error when loading object texture");
	game->list_object[index].obj.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->list_object[index].obj.allocated_img = img;
}

void	init_object(t_game *game)
{
	t_object	tree;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	tree.x = 3.5;
	tree.y = 3.5;
	game->list_object[0] = tree;
	load_object_t(game, 0, "img/object/tree.xpm");
}

void	render_objects(void	*img, t_game *g)
{
	t_object	obj;
	int			i;
	double		fvec_x;
	double		fvec_y;
	double		dist;

	i = 0;
	while (i < 10)
	{

		// fPlayerA = 45 deg = 0,7854 (PI/4) rad
		// FOV video = 90 deg = 1,5708 (PI/2) rad
		// FOV = 2 x artan(0.66) = 2 x 33.4 = 66.8 deg = 1,151917 rad

		// idée : utiliser pythagore
		obj = g->list_object[i];
		// can object be seen ?
		fvec_x = obj.x - g->player.pos.x;
		fvec_y = obj.y - g->player.pos.y;
		dist = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);

		double fObjectAngle = atan2(fvec_x, fvec_y) - atan2( g->player.dir.x , g->player.dir.y);
		if (fObjectAngle < -3.14159f)
			fObjectAngle += 2.0f * 3.14159f;
		if (fObjectAngle > 3.14159f)
			fObjectAngle -= 2.0f * 3.14159f;

		printf(" dist = %f\n", dist);

		// object in FOV
		if (fabs(fObjectAngle) < FOV / 2.0f && sqrt(fvec_x * fvec_x + fvec_y * fvec_y) >= 0.5)
		{
			printf("SEEN\n");
		}
		else
			printf("NOT SEEN\n");



		i++;
	}
}
