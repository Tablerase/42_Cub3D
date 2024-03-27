/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:58:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 13:27:33 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	open_nearby_doors(t_game *game)
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
			{
				game->map.map[y][x] = DOOR_OPEN;
			}
			y++;
		}
		x++;
	}
}

/**
 * @brief Function to check if a door is nearby
 * @param game The game struct
 * @return true If a door is nearby
*/
static bool	door_nearby(t_game *game)
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
			{
				return (true);
			}
			y++;
		}
		x++;
	}
	return (false);
}

void	update_door(t_game *game)
{
	if (door_nearby(game) == true)
	{
		if (game->keys.key_space == PRESSED)
		{
			open_nearby_doors(game);
		}
	}
}