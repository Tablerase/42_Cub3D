/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:27:58 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/12 13:39:17 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	ft_init_game(t_game *game)
{
	game->mlx.mlx = NULL;
	game->mlx.win = NULL;
	game->img.img = NULL;
	game->img.addr = NULL;
	game->img.bpp = 0;
	game->img.line_len = 0;
	game->img.endian = 0;
	game->mouse_x = 0;
	game->mouse_y = 0;
}

static bool	ft_setup_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	if (!game->img.img)
	{
		perror("Mlx image: ");
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		return (false);
	}
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
	{
		perror("Mlx image address: ");
		mlx_destroy_image(game->mlx.mlx, game->img.img);
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		return (false);
	}
	return (true);
}

/**
 * @brief Function to setup the game
 * @param game The game struct
 * @return true If the setup was successful
 * @return false If the setup failed
 * @note The function initializes the mlx and the window
*/
bool	ft_setup(t_game *game)
{
	ft_init_game(game);
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		perror("Mlx init: ");
		return (false);
	}
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->mlx.win)
	{
		perror("Mlx window: ");
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		return (false);
	}
	if (!ft_setup_img(game))
		return (false);
	return (true);
}
