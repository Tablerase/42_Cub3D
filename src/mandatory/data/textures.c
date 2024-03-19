/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:59:33 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/19 17:23:03 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	init_texture(t_game *game, t_texture *texture)
{
	texture->img.img = mlx_xpm_file_to_image(\
		game->mlx.mlx, texture->path, &texture->width, &texture->height);
	if (texture->img.img == NULL)
	{
		printf("%sError:%s Texture not found\n", BRED, RESET);
		return (false);
	}
	texture->img.addr = mlx_get_data_addr(\
		texture->img.img, &texture->img.bpp, \
		&texture->img.line_len, &texture->img.endian);
	if (texture->img.addr == NULL)
	{
		printf("%sError:%s Texture Address not found\n", BRED, RESET);
		return (false);
	}
	return (true);
}

bool	ft_setup_textures(t_game *game)
{
	game->textures.north.height = 32;
	game->textures.north.width = 32;
	game->textures.north.path = "./assets/textures/test-north.xpm";
	if (init_texture(game, &game->textures.north) == false)
		return (false);
	game->textures.south.height = 32;
	game->textures.south.width = 32;
	game->textures.south.path = "./assets/textures/test-south.xpm";
	if (init_texture(game, &game->textures.south) == false)
		return (false);
	game->textures.east.height = 32;
	game->textures.east.width = 32;
	game->textures.east.path = "./assets/textures/test-east.xpm";
	if (init_texture(game, &game->textures.east) == false)
		return (false);
	game->textures.west.height = 32;
	game->textures.west.width = 32;
	game->textures.west.path = "./assets/textures/test-west.xpm";
	if (init_texture(game, &game->textures.west) == false)
		return (false);
	game->textures.floor_color = create_argb(0, 205, 133, 63);
	game->textures.ceiling_color = create_argb(0, 135, 206, 235);
	return (true);
}
