/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:05:05 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/11 14:33:09 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/**
 * @brief Function to handle the key events
 * @param keycode The keycode
 * @param game The game struct
 * @note XK_Escape - The escape key - Exit the program
*/
int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		ft_exit(game);
	return (0);
}

/**
 * @brief Function to handle the mouse position
 * @param mouse_x The x position of the mouse
 * @param mouse_y The y position of the mouse
 * @param game The game struct
 * @note mlx_mouse_get_pos - Get the position of the mouse
*/
int mouse_pos(int mouse_x, int mouse_y, t_game *game)
{
  mlx_mouse_get_pos(game->mlx.mlx, game->mlx.win, &mouse_x, &mouse_y);
  game->mouse_x = mouse_x;
  game->mouse_y = mouse_y;
  return (0);
}

/**
 * @brief Function to handle the events
 * @param game The game struct
 * @note DestroyNotify - The window has been destroyed
*/
void	ft_events(t_game *game)
{
	mlx_key_hook(game->mlx.win, key_hook, game);
	mlx_hook(game->mlx.win, DestroyNotify, NoEventMask, ft_exit, game);
	mlx_hook(game->mlx.win, MotionNotify, PointerMotionMask, mouse_pos, game);
}
