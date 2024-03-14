/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:54:58 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/12 17:00:12 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/**
 * @brief Function to exit the program
 * @param game The game struct
*/
int	ft_exit(t_game *game)
{
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
	exit(0);
	return (0);
}
