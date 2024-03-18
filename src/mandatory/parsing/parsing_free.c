/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:40:21 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 13:13:18 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_free(t_game *game)
{
	int	i;

	if (game == NULL)
		return ;
	if (game->mlx.mlx != NULL)
	{
		if (game->mlx.win != NULL)
			mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		parsing_free_textures(game);
		if (game->map.map != NULL)
		{
			i = 0;
			while (game->map.map[i] != NULL)
				free(game->map.map[i++]);
			free(game->map.map);
		}
		if (game->img.img != NULL)
			mlx_destroy_image(game->mlx.mlx, game->img.img);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
}

void	parsing_free_textures(t_game *game)
{
	if (game->textures.north.path != NULL)
		free(game->textures.north.path);
	if (game->textures.north.img.img != NULL)
		mlx_destroy_image(game->mlx.mlx, game->textures.north.img.img);
	if (game->textures.south.path != NULL)
		free(game->textures.south.path);
	if (game->textures.south.img.img != NULL)
		mlx_destroy_image(game->mlx.mlx, game->textures.south.img.img);
	if (game->textures.west.path != NULL)
		free(game->textures.west.path);
	if (game->textures.west.img.img != NULL)
		mlx_destroy_image(game->mlx.mlx, game->textures.west.img.img);
	if (game->textures.east.path != NULL)
		free(game->textures.east.path);
	if (game->textures.east.img.img != NULL)
		mlx_destroy_image(game->mlx.mlx, game->textures.east.img.img);
}

int	parsing_clean_end(t_game *game)
{
	parsing_free(game);
	exit(0);
}

void	parsing_exit_error(t_game *game)
{
	parsing_free(game);
	write(2, "Error\n", 6);
	exit(1);
}

void	parsing_free_test_map(t_game *game, t_map *test_map, int success)
{
	int	i;

	i = 0;
	while (test_map->map[i] != NULL)
		free(test_map->map[i++]);
	free(test_map->map);
	if (success == 0)
		parsing_exit_error(game);
}
