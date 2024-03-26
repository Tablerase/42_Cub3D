/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 13:55:22 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
	minimap(game);
	return (0);
}

void	ft_setup_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		parsing_exit_error(game, "mlx_new_image() failed\n");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		parsing_exit_error(game, "mlx_get_data_addr() failed\n");
}

void	ft_setup_window(t_game *game)
{
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (game->mlx.win == NULL)
		parsing_exit_error(game, "mlx_new_window() failed\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		parsing_exit_error(NULL, "Invalid number of arguments\n");
	parsing_init(&game);
	parsing(&game, argv[1]);
	ft_setup_img(&game);
	ft_setup_player(&game);
	ft_setup_window(&game);
	ft_events(&game);
	mlx_loop_hook(game.mlx.mlx, ft_gameplay, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
