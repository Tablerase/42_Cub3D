/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_rotations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:25:50 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 14:48:38 by rcutte           ###   ########.fr       */
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
 * @note The deadzone is set to WIDTH / 10
 * @note The player will rotate every x frames to prevent the player from
 * rotating too fast
*/
void	mouse_rotations(t_game *game)
{
	static int	move_count = 0;
	int			deadzone;
	int			middle;
	int			frame_cap;

	deadzone = WIDTH / 10;
	middle = WIDTH / 2;
	frame_cap = 3;
	if (move_count < frame_cap)
	{
		move_count++;
		return ;
	}
	else
	{
		if (game->mouse_x < middle - deadzone)
			rotate_left(game);
		if (game->mouse_x > middle + deadzone)
			rotate_right(game);
		move_count = 0;
	}
}
