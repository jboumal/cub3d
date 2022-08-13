#include "cub3d.h"

int	mouse_hide(t_game *game)
{
    if (LINUX)
	    mlx_mouse_hide(game->mlx, game->window);
    else
        mac_mouse_hide();
	return (0);
}

int	mouse_move(t_game *game, int x, int y)
{
    if (LINUX)
	    mlx_mouse_move(game->mlx, game->window, x, y);
    else
        mac_mouse_move(x, y);
	return (0);
}