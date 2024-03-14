/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:16:39 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/12 17:06:15 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define MAP_HEIGHT 10
#define MAP_WIDTH 10

bool	ft_setup_map(t_game *game)
{
    enum e_tile	**map;
	int	i;
	int	j;

	i = 0;
	map = NULL;
	game->map.height = MAP_HEIGHT;
	game->map.width = MAP_WIDTH;
    map = malloc(MAP_HEIGHT * sizeof(enum e_tile *));
    if (map == NULL)
	{
		return (false);// return false if memory allocation failed
	}
	while (i < MAP_HEIGHT)
	{
		map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < MAP_HEIGHT)
	{
		map[i] = malloc(MAP_WIDTH * sizeof(enum e_tile));
		if (map[i] == NULL) 
			return false; // return false if memory allocation failed
		i++;
	}
	enum e_tile temp_map[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	i = 0;
	while (i < MAP_HEIGHT) {
		j = 0;
		while (j < MAP_WIDTH)
		{
			map[i][j] = temp_map[i][j];
			j++;
		}
		i++;
	}
	game->map.map = map;
    return true;
}
