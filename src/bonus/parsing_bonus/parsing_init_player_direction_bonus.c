/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_player_direction_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:53:41 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 12:00:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	parsing_found_player(t_game *game, char direction, int i, int j)
{
	if (game->player.pos_x != -1 || game->player.pos_y != -1)
		parsing_exit_error(game, "Multiple player definition\n");
	game->map.map[i][j] = GROUND;
	if (direction == 'N')
		parsing_player_north_direction(game);
	if (direction == 'S')
		parsing_player_south_direction(game);
	if (direction == 'W')
		parsing_player_west_direction(game);
	if (direction == 'E')
		parsing_player_east_direction(game);
	game->player.pos_x = j + 0.5;
	game->player.pos_y = i + 0.5;
}

void	parsing_player_north_direction(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

void	parsing_player_south_direction(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	parsing_player_west_direction(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

void	parsing_player_east_direction(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}
