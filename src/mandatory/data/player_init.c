/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:51:35 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/22 10:21:55 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	return (true);
}
