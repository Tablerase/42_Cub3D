/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 15:15:30 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

// void	put_sprite(t_game *game)
// {
// 	char	*dest_sprite;
// 	char	*dest;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < game->sprite.img->on_screen->img.height)
// 	{
// 		j = 0;
// 		while (j < game->sprite.img->on_screen->img.width)
// 		{
// 			dest_sprite = game->sprite.img->on_screen->img.img.addr
// 				+ (j * game->sprite.img->on_screen->img.img.line_len
// 					+ i * (game->sprite.img->on_screen->img.img.bpp / 8));
// 			dest = game->img.addr + (j * game->img.line_len
// 					+ (i + WIDTH - 128) * (game->img.bpp / 8));
// 			if (*(unsigned int *)dest_sprite != 0x00FF00)
// 				*(unsigned int *)dest = *(unsigned int *)dest_sprite;
// 			j++;
// 		}
// 		i++;
// 	}
// }

/**
 * @brief Function to handle the game play
 * @param game The game struct
 * @note This function will be used to handle the game play
 * (movement, raycasting, etc)
*/
int	ft_gameplay(t_game *game)
{
	static int	time;

	time++;
	raycasting(game);
	if (time > 7)
	{
		time = 0;
		game->sprite.img->on_screen->is_on_screen = false;
		game->sprite.img->on_screen = game->sprite.img->on_screen->next;
		game->sprite.img->on_screen->is_on_screen = true;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img.img, 0, 0);
	update_movement(game);
	update_door(game);
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
	if (game->sprite.nb_sprites == 0)
		return ;
	game->sprite.z_buffer = malloc(WIDTH * sizeof(double));
	if (game->sprite.z_buffer == NULL)
		parsing_exit_error(game, "Allocation failed\n");
	game->sprite.sprite_order = malloc(game->sprite.nb_sprites
			* sizeof(int));
	if (game->sprite.sprite_order == NULL)
		parsing_exit_error(game, "Allocation failed\n");
	game->sprite.sprite_distance = malloc(game->sprite.nb_sprites
			* sizeof(double));
	if (game->sprite.sprite_distance == NULL)
		parsing_exit_error(game, "Allocation failed\n");
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
	ft_setup_door_and_sprite(&game);
	ft_setup_window(&game);
	ft_events(&game);
	mlx_loop_hook(game.mlx.mlx, ft_gameplay, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
