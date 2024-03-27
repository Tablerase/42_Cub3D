/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_movements_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:08:24 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 11:55:03 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Function to move the player forward
 * @param game The game struct
 * @note Check if the next position is a ground
 * @note increment the position of the player according to vector direction
 * with the move_speed
*/
void	move_forward(t_game *game)
{
	if (game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		+ game->player.dir_x * game->player.move_speed)] == GROUND
		|| game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		+ game->player.dir_x * game->player.move_speed)] == DOOR_OPEN)
	{
		game->player.pos_x += game->player.dir_x * game->player.move_speed;
	}
	if (game->map.map[(int)(game->player.pos_y + game->player.dir_y
			* game->player.move_speed)][(int)game->player.pos_x] == GROUND
			|| game->map.map[(int)(game->player.pos_y + game->player.dir_y
			* game->player.move_speed)][(int)game->player.pos_x] == DOOR_OPEN)
	{
		game->player.pos_y += game->player.dir_y * game->player.move_speed;
	}
}

/**
 * @brief Function to move the player backward
 * @param game The game struct
 * @note Check if the next position is a ground
 * @note decrement the position of the player according to vector direction
 * with the move_speed
*/
void	move_backward(t_game *game)
{
	if (game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		- game->player.dir_x * game->player.move_speed)] == GROUND
		|| game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		- game->player.dir_x * game->player.move_speed)] == DOOR_OPEN)
	{
		game->player.pos_x -= game->player.dir_x * game->player.move_speed;
	}
	if (game->map.map[(int)(game->player.pos_y - game->player.dir_y
			* game->player.move_speed)][(int)game->player.pos_x] == GROUND
			|| game->map.map[(int)(game->player.pos_y - game->player.dir_y
			* game->player.move_speed)][(int)game->player.pos_x] == DOOR_OPEN)
	{
		game->player.pos_y -= game->player.dir_y * game->player.move_speed;
	}
}

/**
 * @brief Function to move the player left
 * @param game The game struct
 * @note Check if the next position is a ground
 * @note decrement the position of the player according to the plane vector
 * (horizontal to dir of player) with the move_speed
*/
void	move_left(t_game *game)
{
	if (game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		- game->player.plane_x * game->player.move_speed)] == GROUND
		|| game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		- game->player.plane_x * game->player.move_speed)] == DOOR_OPEN)
	{
		game->player.pos_x -= game->player.plane_x * game->player.move_speed;
	}
	if (game->map.map[(int)(game->player.pos_y - game->player.plane_y
			* game->player.move_speed)][(int)game->player.pos_x] == GROUND
			|| game->map.map[(int)(game->player.pos_y - game->player.plane_y
			* game->player.move_speed)][(int)game->player.pos_x] == DOOR_OPEN)
	{
		game->player.pos_y -= game->player.plane_y * game->player.move_speed;
	}
}

/**
 * @brief Function to move the player right
 * @param game The game struct
 * @note Check if the next position is a ground
 * @note increment the position of the player according to the plane vector
 * (horizontal to dir of player) with the move_speed
*/
void	move_right(t_game *game)
{
	if (game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		+ game->player.plane_x * game->player.move_speed)] == GROUND
		|| game->map.map[(int)game->player.pos_y][(int)(game->player.pos_x
		+ game->player.plane_x * game->player.move_speed)] == DOOR_OPEN)
	{
		game->player.pos_x += game->player.plane_x * game->player.move_speed;
	}
	if (game->map.map[(int)(game->player.pos_y + game->player.plane_y
			* game->player.move_speed)][(int)game->player.pos_x] == GROUND
			|| game->map.map[(int)(game->player.pos_y + game->player.plane_y
			* game->player.move_speed)][(int)game->player.pos_x] == DOOR_OPEN)
	{
		game->player.pos_y += game->player.plane_y * game->player.move_speed;
	}
}

/**
 * @brief Function to update the movement of the player
 * @param game The game struct
 * @note Check if the keys are pressed or if the mouse is moved
 * and update the movement of the player accordingly
*/
void	update_movement(t_game *game)
{
	if (game->keys.key_w)
		move_forward(game);
	if (game->keys.key_s)
		move_backward(game);
	if (game->keys.key_a)
		move_left(game);
	if (game->keys.key_d)
		move_right(game);
	if (game->keys.key_left)
		rotate_left(game);
	if (game->keys.key_right)
		rotate_right(game);
	mouse_rotations(game);
}
