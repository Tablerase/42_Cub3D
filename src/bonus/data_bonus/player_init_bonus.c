/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:51:35 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 14:12:14 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Function to setup the player
 * @param game The game struct
 * @return true if the setup was successful, false otherwise
*/
bool	ft_setup_player(t_game *game)
{
	game->player.fov = 66;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.02;
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	return (true);
}
