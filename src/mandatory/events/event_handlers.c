/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:05:05 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/14 19:18:07 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// /**
//  * @brief Function to handle the key events
//  * @param keycode The keycode
//  * @param game The game struct
//  * @note XK_Escape - The escape key - Exit the program
// */
// int	key_hook(int keycode, t_game *game)
// {
// 	if (keycode == XK_Escape)
// 		ft_exit(game);
// 	return (0);
// }

void	init_keys(t_game *game)
{
	game->keys.key_a = 0;
	game->keys.key_w = 0;
	game->keys.key_s = 0;
	game->keys.key_d = 0;
	game->keys.key_left = 0;
	game->keys.key_right = 0;
}

int	on_click(int keycode, t_game *game)
{
	if (keycode == XK_a)
		game->keys.key_a = PRESSED;
	if (keycode == XK_s)
		game->keys.key_s = PRESSED;
	if (keycode == XK_w)
		game->keys.key_w = PRESSED;
	if (keycode == XK_d)
		game->keys.key_d = PRESSED;
	if (keycode == XK_Left)
		game->keys.key_left = PRESSED;
	if (keycode == XK_Right)
		game->keys.key_right = PRESSED;
	if (keycode == XK_Escape)
		ft_exit(game);
	return (1);
}

int	on_release(int keycode, t_game *game)
{
	if (keycode == XK_a)
		game->keys.key_a = RELEASED;
	if (keycode == XK_s)
		game->keys.key_s = RELEASED;
	if (keycode == XK_w)
		game->keys.key_w = RELEASED;
	if (keycode == XK_d)
		game->keys.key_d = RELEASED;
	if (keycode == XK_Left)
		game->keys.key_left = RELEASED;
	if (keycode == XK_Right)
		game->keys.key_right = RELEASED;
	return (1);
}

/**
 * @brief Function to handle the mouse position
 * @param mouse_x The x position of the mouse
 * @param mouse_y The y position of the mouse
 * @param game The game struct
 * @note mlx_mouse_get_pos - Get the position of the mouse
*/
int	mouse_pos(int mouse_x, int mouse_y, t_game *game)
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
 * @note MotionNotify - The mouse has been moved
*/
void	ft_events(t_game *game)
{
	mlx_hook(game->mlx.win, KeyPress, KeyPressMask, &on_click, game);
	mlx_hook(game->mlx.win, KeyRelease, KeyReleaseMask, &on_release, game);
	mlx_hook(game->mlx.win, DestroyNotify, NoEventMask, ft_exit, game);
	mlx_hook(game->mlx.win, MotionNotify, PointerMotionMask, mouse_pos, game);
}
