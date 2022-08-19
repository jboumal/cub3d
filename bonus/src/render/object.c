/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/19 22:46:20 by bperraud         ###   ########.fr       */
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
	tree.y = 7.5;
	tree.size = 0.5;
	game->list_object[0] = tree;
	load_object_t(game, 0, "img/object/tree.xpm");
}

void	render_objects(void	*img, t_game *g)
{
	t_object	obje;
	int			i;
	double		fvec_x;
	double		fvec_y;
	double		dist;
	double		fObjectAngle;

	i = 0;
	while (i < 1)
	{
		// fPlayerA = 45 deg = 0,7854 (PI/4) rad
		// FOV video = 90 deg = 1,5708 (PI/2) rad
		// FOV = 2 x artan(0.66) = 2 x 33.4 = 66.8 deg = 1,151917 rad

		obje = g->list_object[i];
		// can object be seen ?
		fvec_x = obje.x - g->player.pos.x;
		fvec_y = obje.y - g->player.pos.y;
		dist = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);

		fObjectAngle = atan2(fvec_x, fvec_y) - atan2( g->player.dir.x , g->player.dir.y);
		if (fObjectAngle < -3.14159)
			fObjectAngle += 2.0 * 3.14159;
		if (fObjectAngle > 3.14159f)
			fObjectAngle -= 2.0 * 3.14159;

		// pb de FOV ?
		// object is in FOV
		if (fabs(fObjectAngle) < FOV / 2.0 && sqrt(fvec_x * fvec_x + fvec_y * fvec_y) >= 1.0)
		{
			double fObjectCeiling = (((double) SCREEN_H / 2.0) - ((double) SCREEN_H / ((double) dist / obje.size)));
			double fObjectHeight = (double) SCREEN_H - 2.0 * fObjectCeiling;
			double fObjectAspectRatio = (double) obje.obj.height  / (double) obje.obj.width ;
			double fObjectWidth = fObjectHeight / fObjectAspectRatio;
			double fMiddleOfObject = (0.5 * (fObjectAngle / (FOV / 2.0)) + 0.5) * (double) SCREEN_W;

			// Draw tree
			for (double lx = 0; lx < fObjectWidth; lx++)
			{
				for (double ly = 0; ly < fObjectHeight; ly++)
				{
					double fSampleX = lx / fObjectWidth * (double) obje.obj.width;
					double fSampleY = ly / fObjectHeight * (double) obje.obj.height;
					int tex = ((int) fSampleY * obje.obj.height + (int) fSampleX);
					int color = obje.obj.img[tex];
					int nObjectColumn = (int)(fMiddleOfObject + lx - (fObjectWidth / 2.0));

					if (nObjectColumn >= 0 && nObjectColumn < SCREEN_W)
					{
						if (color > 0)
							my_mlx_pixel_put(img, (int) nObjectColumn, (int) fObjectCeiling + ly, color);
						//fDepthBuffer[nObjectColumn] = dist;
					}
				}
			}
		}
		i++;
	}
}
