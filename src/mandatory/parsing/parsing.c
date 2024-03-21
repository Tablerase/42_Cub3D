/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:32:22 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/21 19:01:00 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_file_name_and_format(t_game *game, char *filename)
{
	int	i;
	int	fd_dir;

	i = ft_strlen(filename);
	if (i < 4)
		parsing_exit_error(game);
	if (!(filename[--i] == 'b' && filename[--i] == 'u'
			&& filename[--i] == 'c' && filename[--i] == '.'))
		parsing_exit_error(game);
	fd_dir = open(filename, O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		parsing_exit_error(game);
	}
	return ;
}

// called in main
void	parsing(t_game *game, char *filename)
{
	t_fds	fd;

	parsing_file_name_and_format(game, filename);
	fd.fd1 = open(filename, O_RDONLY);
	if (fd.fd1 == -1)
		parsing_exit_error(game);
	fd.fd2 = open(filename, O_RDONLY);
	if (fd.fd2 == -1)
	{
		close(fd.fd1);
		parsing_exit_error(game);
	}
	parsing_textures(game, fd);
	parse_map(game, fd);
	return ;
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	if (argc != 2)
// 		parsing_exit_error(NULL);
// 	parsing_init(&game);
// 	parsing(&game, argv[1]);
// 	game.mlx.win = mlx_new_window(game.mlx.mlx, WIDTH, HEIGHT, "cub3d");
// 	if (game.mlx.win == NULL)
// 		parsing_exit_error(&game);
// 	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win,
// 		game.textures.north.img.img, 0, 0);
// 	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win,
// 		game.textures.south.img.img, WIDTH / 2, 0);
// 	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win,
// 		game.textures.west.img.img, 0, HEIGHT / 2);
// 	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win,
// 		game.textures.east.img.img, WIDTH / 2, HEIGHT / 2);
// 	mlx_pixel_put(game.mlx.mlx, game.mlx.win, WIDTH / 4, HEIGHT / 2,
// 		game.textures.ceiling_color);
// 	mlx_pixel_put(game.mlx.mlx, game.mlx.win, WIDTH / 4, HEIGHT / 4,
// 		game.textures.floor_color);
// 	mlx_hook(game.mlx.win, 17, 0, &parsing_clean_end, &game);
// 	mlx_loop(game.mlx.mlx);
// 	parsing_free(&game);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_game	game;
//
// 	if (argc != 2)
// 		parsing_exit_error(NULL);
// 	if (ft_setup_player(&game) == false)
// 		return (EXIT_FAILURE);
// 	parsing_init(&game);
// 	parsing(&game, argv[1]);
// 	game.mlx.win = mlx_new_window(game.mlx.mlx, WIDTH, HEIGHT, "cub3d");
// 	if (game.mlx.win == NULL)
// 		parsing_exit_error(&game);
// 	if (!ft_setup_img(&game))
// 		parsing_exit_error(&game);
// 	ft_events(&game);
// 	mlx_loop_hook(game.mlx.mlx, ft_gameplay, &game);
// 	mlx_loop(game.mlx.mlx);
// 	parsing_free(&game); // useless exiting with Escape or x
// 	return (0);
// }
//
// strtrim with tabs