/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:56:36 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 14:19:59 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_init(t_game *game)
{
	game->mlx.mlx = NULL;
	game->mlx.win = NULL;
	game->img.img = NULL;
	game->img.addr = NULL;
	game->keys.key_a = RELEASED;
	game->keys.key_w = RELEASED;
	game->keys.key_s = RELEASED;
	game->keys.key_d = RELEASED;
	game->keys.key_left = RELEASED;
	game->keys.key_right = RELEASED;
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	parsing_init_textures(game);
	game->mlx.mlx = mlx_init();
	if (game->mlx.mlx == NULL)
		parsing_exit_error(game, "mlx_init() failed\n");
	game->player.pos_x = -1;
	game->player.pos_y = -1;
}

void	parsing_init_textures(t_game *game)
{
	game->textures.north.path = NULL;
	game->textures.north.img.img = NULL;
	game->textures.north.type = NORTH;
	game->textures.south.path = NULL;
	game->textures.south.img.img = NULL;
	game->textures.south.type = SOUTH;
	game->textures.west.path = NULL;
	game->textures.west.img.img = NULL;
	game->textures.west.type = WEST;
	game->textures.east.path = NULL;
	game->textures.east.img.img = NULL;
	game->textures.east.type = EAST;
}

void	parsing_init_test_map(t_game *game, t_map *test_map)
{
	int	i;

	i = 0;
	test_map->height = game->map.height;
	test_map->width = game->map.width;
	test_map->map = malloc((test_map->height + 1) * sizeof(enum e_tile *));
	if (test_map->map == NULL)
		parsing_exit_error(game, "Test map allocation failed\n");
	while (i < game->map.height)
	{
		test_map->map[i] = malloc(test_map->width * sizeof(enum e_tile));
		if (test_map->map[i] == NULL)
		{
			while (--i >= 0)
				free(test_map->map[i]);
			free(test_map->map);
			parsing_exit_error(game, "Sub test map allocation failed\n");
		}
		i++;
	}
	test_map->map[i] = NULL;
}
