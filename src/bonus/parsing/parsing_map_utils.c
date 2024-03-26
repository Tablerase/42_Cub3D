/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:15:45 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/25 11:35:47 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_find_start_index(t_game *game, int *i_start, int *j_start)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] != EMPTY)
			{
				*i_start = i;
				*j_start = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	parsing_fill_test_map(t_game *game, t_map *test_map)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (j < game->map.width)
		{
			test_map->map[i][j] = game->map.map[i][j];
			j++;
		}
		i++;
	}
}

void	parsing_check_nb_island(t_game *game, t_map *test_map)
{
	int	i;
	int	j;

	i = 0;
	while (test_map->map[i] != NULL)
	{
		j = 0;
		while (j < test_map->width)
		{
			if (test_map->map[i][j] != EMPTY)
				parsing_free_test_map(game, test_map, 0, "Too many maps\n");
			j++;
		}
		i++;
	}
}

void	parsing_fill_first_island(t_map *map, int i, int j)
{
	map->map[i][j] = EMPTY;
	if (j > 0 && map->map[i][j - 1] != EMPTY)
		parsing_fill_first_island(map, i, j - 1);
	if (j > 0 && i > 0 && map->map[i - 1][j - 1] != EMPTY)
		parsing_fill_first_island(map, i - 1, j - 1);
	if (j > 0 && i < map->height - 1 && map->map[i + 1][j - 1] != EMPTY)
		parsing_fill_first_island(map, i + 1, j - 1);
	if (j < map->width - 1 && map->map[i][j + 1] != EMPTY)
		parsing_fill_first_island(map, i, j + 1);
	if (j < map->width - 1 && i > 0 && map->map[i - 1][j + 1] != EMPTY)
		parsing_fill_first_island(map, i - 1, j + 1);
	if (j < map->width - 1 && i < map->height - 1
		&& map->map[i + 1][j + 1] != EMPTY)
		parsing_fill_first_island(map, i + 1, j + 1);
	if (i > 0 && map->map[i - 1][j] != EMPTY)
		parsing_fill_first_island(map, i - 1, j);
	if (i < map->height - 1 && map->map[i + 1][j] != EMPTY)
		parsing_fill_first_island(map, i + 1, j);
}

void	free_parse_map(t_game *game, int fd2, char *error_msg)
{
	close(fd2);
	parsing_exit_error(game, error_msg);
}
