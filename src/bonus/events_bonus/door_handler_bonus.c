/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:58:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 17:03:36 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	action_on_nearby_doors(t_game *game)
{
	int			x;
	int			y;
	int			range;
	enum e_tile	tile;

	range = 1;
	x = (int)game->player.pos_x - range;
	y = (int)game->player.pos_y - range;
	while (x <= game->map.width - 1 && x <= game->player.pos_x + range
		&& x >= 0)
	{
		y = (int)game->player.pos_y - range;
		while (y <= game->map.height - 1 && y <= game->player.pos_y + range
			&& y >= 0)
		{
			tile = game->map.map[y][x];
			if (tile == DOOR_CLOSED)
				game->map.map[y][x] = DOOR_OPEN;
			else if (tile == DOOR_OPEN)
				game->map.map[y][x] = DOOR_CLOSED;
			y++;
		}
		x++;
	}
}

/**
 * @brief Function to check if a door is nearby
 * @param game The game struct
 * @return The tile type of the door if found, EMPTY otherwise
*/
static enum e_tile	door_nearby(t_game *game)
{
	int			x;
	int			y;
	int			range;
	enum e_tile	tile;

	range = 1;
	x = (int)game->player.pos_x - range;
	y = (int)game->player.pos_y - range;
	while (x <= game->map.width - 1 && x <= game->player.pos_x + range
		&& x >= 0)
	{
		y = (int)game->player.pos_y - range;
		while (y <= game->map.height - 1 && y <= game->player.pos_y + range
			&& y >= 0)
		{
			tile = game->map.map[y][x];
			if (tile == DOOR_CLOSED || tile == DOOR_OPEN)
				return (tile);
			y++;
		}
		x++;
	}
	return (EMPTY);
}

void	update_door(t_game *game)
{
	static int		frame;
	enum e_tile		tile;

	tile = game->map.map[(int)game->player.pos_y][(int)game->player.pos_x];
	if (frame == 10)
	{
		if (door_nearby(game) != EMPTY)
		{
			if (game->keys.key_space == PRESSED
				&& tile != DOOR_CLOSED && tile != DOOR_OPEN)
			{
				action_on_nearby_doors(game);
			}
		}
		frame = 0;
	}
	else
		frame++;
}
