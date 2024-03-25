/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_valid_tiles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:10:50 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/25 11:47:52 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	is_edge(t_map map, int i, int j)
{
	if (i == 0 || j == 0 || i == map.height - 1 || j == map.width - 1)
		return (1);
	return (0);
}

int	unclosed_ground(t_map map, int i, int j)
{
	if (j > 0)
	{
		if (map.map[i][j - 1] == EMPTY)
			return (1);
	}
	if (j < map.width)
	{
		if (map.map[i][j + 1] == EMPTY)
			return (1);
	}
	if (i > 0)
	{
		if (map.map[i - 1][j] == EMPTY)
			return (1);
	}
	if (i < map.height)
	{
		if (map.map[i + 1][j] == EMPTY)
			return (1);
	}
	return (0);
}

// unused
// void	parsing_count_player_map(t_game *game)
// {
// 	int	count;
// 	int	i;
// 	int	j;

// 	count = 0;
// 	i = 0;
// 	while (game->map.map[i] != NULL)
// 	{
// 		j = 0;
// 		while (j < game->map.width)
// 		{
// 			if (game->map.map[i][j] == PLAYER)
// 				count++;
// 			if (count > 1)
// 				parsing_exit_error(game);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (count != 1)
// 		parsing_exit_error(game);
// }
