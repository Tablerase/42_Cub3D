/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:28:30 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 18:13:44 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

static void	put_help_msg(t_game *game)
{
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 15, 0x00FFFFFF,
		"Press 'W' to move forward");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 35, 0x00FFFFFF,
		"Press 'S' to move backward");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 55, 0x00FFFFFF,
		"Press 'A' to move left");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 75, 0x00FFFFFF,
		"Press 'D' to move right");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 95, 0x00FFFFFF,
		"Press 'Arrow left' to rotate left");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 115, 0x00FFFFFF,
		"Press 'Arrow right' to rotate right");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 135, 0x00FFFFFF,
		"Press 'Space' to open the doors");
	mlx_string_put(game->mlx.mlx, game->mlx.win, WIDTH - 250, 155, 0x00FFFFFF,
		"Press 'ESC' to quit the game");
}

/**
 * @brief Function to display the user help
 * @param game The game struct
 * @note This function will be used to display the user help
*/
void	user_help(t_game *game)
{
	if (game->keys.key_h == PRESSED)
	{
		put_help_msg(game);
	}
	mlx_string_put(game->mlx.mlx, game->mlx.win, 30, 10, 0x00FFFFFF,
		"Press 'H' for help");
}
