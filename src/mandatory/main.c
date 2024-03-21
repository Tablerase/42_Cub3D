/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/21 19:09:04 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	transparency(int alpha, int color, int background_color)
{
	int	transparent_r;
	int	transparent_g;
	int	transparent_b;

	transparent_r = ((color >> 16) * alpha / 255) + (background_color >> 16) * (255 - alpha) / 255;
	transparent_g = (((color >> 8) - ((color >> 16) << 8)) * alpha / 255) + ((background_color >> 8) - ((background_color >> 16) << 8)) * (255 - alpha) / 255;
	transparent_b = ((color % 256) * alpha / 255) + (background_color % 256) * (255 - alpha) / 255;
	return (transparent_r << 16 | transparent_g << 8 | transparent_b);
}

void	minimap_cell_color(t_game *game, t_minimap *m, int i, int j)
{
	if (!(i >= 0 && i < game->map.height && j >= 0 && j < game->map.width))
		m->color = transparency(127, 0xFFFFFF, *(unsigned int *)(game->img.addr
			+ (m->pixel_y * game->img.line_len + m->pixel_x
			* (game->img.bpp / 8))));
	else if (game->map.map[i][j] == DOOR)
		m->color = 0x468499;
	else if (game->map.map[i][j] == GROUND)
		m->color = 0xcd853f;
	else if (game->map.map[i][j] == WALL)
		m->color = 0x000000;
	else if (game->map.map[i][j] != EMPTY)
		m->color = -1;
	else
		m->color = 0x0000FF;
	if (j == (int)game->player.pos_x && i == (int)game->player.pos_y)
		m->color = 0xFF0000;
}

void	minimap_cell_draw(t_game *game, t_minimap *m)
{
	char	*dest;
	int		len;
	int		bpp;

	len = game->img.line_len;
	bpp = game->img.bpp / 8;
	dest = game->img.addr + ((m->pixel_y++) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + ((m->pixel_y++) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + (m->pixel_y * len + (m->pixel_x++) * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + ((m->pixel_y - 2) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + ((m->pixel_y - 1) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + (m->pixel_y * len + (m->pixel_x++) * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + ((m->pixel_y - 2) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + ((m->pixel_y - 1) * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
	dest = game->img.addr + (m->pixel_y * len + m->pixel_x * bpp);
	*(unsigned int *)dest = m->color;
}

void	minimap_init(t_game *game, t_minimap *m)
{
	m->pixel_x = 10;
	m->pixel_y = 10;
	m->start_i = game->player.pos_y - 25;
	m->end_i = m->start_i + 50;
	m->start_j = game->player.pos_x - 25;
	m->end_j = m->start_j + 50;
	m->color = 0x000000;
}

void	minimap(t_game *game)
{
	t_minimap	m;
	int			i;
	int			j;

	minimap_init(game, &m);
	i = m.start_i;
	while (i < m.end_i)
	{
		j = m.start_j;
		m.pixel_x = 10;
		m.pixel_y += 3;
		while (j < m.end_j)
		{
			minimap_cell_color(game, &m, i, j);
			if (m.color != -1)
			{
				minimap_cell_draw(game, &m);
				m.pixel_x++;
				m.pixel_y -= 2;
			}
			else
				m.pixel_x += 3;
			j++;
		}
		i++;
	}
}

/**
 * @brief Function to handle the game play
 * @param game The game struct
 * @note This function will be used to handle the game play
 * (movement, raycasting, etc)
*/
int	 ft_gameplay(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img.img, 0, 0);
	update_movement(game);
	minimap(game);
	return (0);
}

// int	main(void)
// {
// 	t_game	game;

// 	if (ft_setup_player(&game) == false)
// 		return (EXIT_FAILURE);
// 	if (ft_setup_map(&game) == false)
// 		return (EXIT_FAILURE);
// 	if (ft_setup(&game) == false)
// 		return (ft_exit(&game), EXIT_FAILURE);
// 	if (ft_setup_textures(&game) == false)
// 		return (EXIT_FAILURE);
// 	ft_events(&game);
// 	mlx_loop_hook(game.mlx.mlx, ft_gameplay, &game);
// 	mlx_loop(game.mlx.mlx);
// 	ft_exit(&game);
// 	return (0);
// }

void	ft_setup_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		parsing_exit_error(game);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		parsing_exit_error(game);
}

void	ft_setup_window(t_game *game)
{
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (game->mlx.win == NULL)
		parsing_exit_error(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		parsing_exit_error(NULL);
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
