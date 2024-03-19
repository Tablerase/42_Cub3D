/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:59:33 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/19 15:27:32 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	ft_setup_textures(t_game *game)
{
	t_texture	*texture;

	texture = &game->textures.north;
	// Get path of the texture
	texture->path = "./assets/textures/japan-wall-tatami.xpm";
	// Initialize the texture info
	texture->type = NORTH;
	// Get size of the texture
	texture->height = 32;
	texture->width = 32;
	// Load the texture
	texture->img.img = mlx_xpm_file_to_image(game->mlx.mlx, texture->path, &texture->width, &texture->height);
	if (texture->img.img == NULL)
	{
		printf("%sError:%s Texture not found\n", BRED, RESET);
		return (false);
	}
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp, &texture->img.line_len, &texture->img.endian);
	if (texture->img.addr == NULL)
	{
		printf("%sError:%s Texture Address not found\n", BRED, RESET);
		return (false);
	}
	game->textures.south = game->textures.north;
	game->textures.east = game->textures.north;
	game->textures.west = game->textures.north;

	// Set the floor and ceiling color
	game->textures.floor_color = create_argb(0, 205, 133, 63);
	game->textures.ceiling_color = create_argb(0, 135, 206, 235);
	return (true);
}
