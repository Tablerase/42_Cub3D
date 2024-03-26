/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_rotations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:25:50 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 14:14:06 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Function to rotate the player to the left
 * @param game The game struct
 * @note Update the direction and plane vectors of the player according to
 * the rotation speed. Increment the rotation speed.
 * @note Matrix 2D rotation
*/
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = game->player.rot_speed;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

/**
 * @brief Function to rotate the player to the right
 * @param game The game struct
 * @note Update the direction and plane vectors of the player according to
 * the rotation speed. Decrement the rotation speed.
 * @note Matrix 2D rotation
*/
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = game->player.rot_speed;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed)
		+ game->player.dir_y * cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed)
		+ game->player.plane_y * cos(-rot_speed);
}

/**
 * @brief Function to handle the mouse rotations
 * @param game The game struct
 * @note Check if the mouse is on the left or right side of the screen
 * and rotate the player accordingly
 * @note The deadzone is set to WIDTH / 10 to prevent the player from
 * rotating too fast
*/
void	mouse_rotations(t_game *game)
{
	if (game->mouse_x < WIDTH / 2 - WIDTH / 10)
		rotate_left(game);
	if (game->mouse_x > WIDTH / 2 + WIDTH / 10)
		rotate_right(game);
}
