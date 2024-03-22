/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:17:59 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/22 10:35:58 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_map_single(t_game *game)
{
	int		i;
	int		j;
	t_map	test_map;

	parsing_init_test_map(game, &test_map);
	parsing_fill_test_map(game, &test_map);
	parsing_find_start_index(game, &i, &j);
	parsing_fill_first_island(&test_map, i, j);
	parsing_check_nb_island(game, &test_map);
	parsing_free_test_map(game, &test_map, 1);
}

void	parsing_map_closed_and_single(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (is_edge(game->map, i, j) == 1
				&& game->map.map[i][j] == GROUND)
				parsing_exit_error(game);
			if ((game->map.map[i][j] == GROUND)
				&& unclosed_ground(game->map, i, j) == 1)
				parsing_exit_error(game);
			j++;
		}
		i++;
	}
	parsing_map_single(game);
}

void	parse_map(t_game *game, t_fds fd)
{
	int	i;

	parsing_width_height_map(game, fd);
	close(fd.fd1);
	fd.fd1 = -1;
	if (game->map.height == 0 || game->map.width == 0)
		free_parse_map(game, fd.fd2);
	game->map.map = malloc((game->map.height + 1) * sizeof(enum e_tile *));
	if (game->map.map == NULL)
		free_parse_map(game, fd.fd2);
	i = 0;
	while (i < game->map.height)
	{
		game->map.map[i] = malloc(game->map.width * sizeof(enum e_tile));
		if (game->map.map[i] == NULL)
			free_parse_map(game, fd.fd2);
		i++;
	}
	game->map.map[i] = NULL;
	parsing_collect_map(game, fd);
	close(fd.fd2);
	parsing_map_closed_and_single(game);
}
