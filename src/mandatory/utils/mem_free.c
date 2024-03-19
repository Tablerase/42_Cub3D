/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:54:58 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/19 15:26:38 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	free_textures(t_game *game)
{
	if (game->textures.north.img.img != NULL)
		mlx_destroy_image(game->mlx.mlx, game->textures.north.img.img);
	// mlx_destroy_image(game->mlx.mlx, game->textures.south.img.img);
	// free(game->textures.south.img.addr);
	// mlx_destroy_image(game->mlx.mlx, game->textures.east.img.img);
	// free(game->textures.east.img.addr);
	// mlx_destroy_image(game->mlx.mlx, game->textures.west.img.img);
	// free(game->textures.west.img.addr);
}

void	ft_free_all(t_game *game)
{
	free_textures(game);
	if (game->map.map != NULL)
	{
		while (game->map.height-- > 0)
		{
			free(game->map.map[game->map.height]);
		}
		free(game->map.map);
	}
	if (game->img.img != NULL)
	{
		mlx_destroy_image(game->mlx.mlx, game->img.img);
	}
	if (game->mlx.win != NULL)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx != NULL)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
}

/**
 * @brief Function to exit the program
 * @param game The game struct
*/
int	ft_exit(t_game *game)
{
	ft_free_all(game);
	exit(EXIT_SUCCESS);
	return (0);
}
