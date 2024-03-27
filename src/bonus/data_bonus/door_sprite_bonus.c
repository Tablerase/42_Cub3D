/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:21:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 12:34:58 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	ft_setup_door_and_sprite(t_game *game)
{
	t_texture *texture;

	texture = &game->textures.door;
	texture->path = "./assets/textures/wooden-door.xpm";
	texture->img.img = mlx_xpm_file_to_image(game->mlx.mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img.img)
		parsing_exit_error(game, "door mlx_xpm_file_to_image() failed\n");
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp,
			&texture->img.line_len, &texture->img.endian);
	if (!texture->img.addr)
		parsing_exit_error(game, "door mlx_get_data_addr() failed\n");
}