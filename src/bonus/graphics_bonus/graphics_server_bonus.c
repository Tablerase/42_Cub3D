/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_server_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:27:58 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 12:00:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

// static void	ft_init_game(t_game *game)
// {
// 	game->mlx.mlx = NULL;
// 	game->mlx.win = NULL;
// 	game->img.img = NULL;
// 	game->img.addr = NULL;
// 	game->img.bpp = 0;
// 	game->img.line_len = 0;
// 	game->img.endian = 0;
// 	game->mouse_x = 0;
// 	game->mouse_y = 0;
// 	game->keys.key_w = RELEASED;
// 	game->keys.key_a = RELEASED;
// 	game->keys.key_s = RELEASED;
// 	game->keys.key_d = RELEASED;
// 	game->keys.key_left = RELEASED;
// 	game->keys.key_right = RELEASED;
// }

// /**
//  * @brief Function to setup the game
//  * @param game The game struct
//  * @return true If the setup was successful
//  * @return false If the setup failed
//  * @note The function initializes the mlx and the window
// */
// bool	ft_setup(t_game *game)
// {
// 	ft_init_game(game);
// 	game->mlx.mlx = mlx_init();
// 	if (!game->mlx.mlx)
// 	{
// 		perror("Mlx init: ");
// 		return (false);
// 	}
// 	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
// 	if (!game->mlx.win)
// 	{
// 		perror("Mlx window: ");
// 		mlx_destroy_display(game->mlx.mlx);
// 		free(game->mlx.mlx);
// 		return (false);
// 	}
// 	if (!ft_setup_img(game))
// 		return (false);
// 	return (true);
// }
