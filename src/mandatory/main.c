/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/19 15:13:18 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Function to handle the game play
 * @param game The game struct
 * @note This function will be used to handle the game play
 * (movement, raycasting, etc)
*/
int	ft_gameplay(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img.img, 0, 0);
	update_movement(game);
	return (0);
}

int	main(void)
{
	t_game	game;

	if (ft_setup_player(&game) == false)
		return (EXIT_FAILURE);
	if (ft_setup_map(&game) == false)
		return (EXIT_FAILURE);
	if (ft_setup(&game) == false)
		return (ft_exit(&game), EXIT_FAILURE);
	if (ft_setup_textures(&game) == false)
		return (EXIT_FAILURE);
	ft_events(&game);
	mlx_loop_hook(game.mlx.mlx, ft_gameplay, &game);
	mlx_loop(game.mlx.mlx);
	ft_exit(&game);
	return (0);
}
