#include "cub3d.h"

int	mouse_hide(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->window);
	return (0);
}

int	mouse_move(t_game *game, int x, int y)
{
	mlx_mouse_move(game->mlx, game->window, x, y);
	return (0);
}