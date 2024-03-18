/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:49:34 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/18 12:52:55 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/**
 * @brief Find the texture of the wall
 * @param game The game struct
 * @param ray The ray struct
*/
void	find_tile_texture(t_game *game, t_ray *ray)
{
	t_texture	*texture;

	if (ray->texture == NORTH)
		texture = &game->textures.north;
	else if (ray->texture == SOUTH)
		texture = &game->textures.south;
	else if (ray->texture == EAST)
		texture = &game->textures.east;
	else
		texture = &game->textures.west;
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	printf("ray->tex_x: %d\n", ray->tex_x);
	if (ray->side == NS && ray->ray_dir_y > 0)
	{
		ray->tex_x = texture->width - ray->tex_x - 1;
		printf("Cond NS ray->tex_x: %d\n", ray->tex_x);
	}
	if (ray->side == EW && ray->ray_dir_x < 0)
	{
		ray->tex_x = texture->width - ray->tex_x - 1;
		printf("Cond EW ray->tex_x: %d\n", ray->tex_x);
	}
}

/**
 * @brief Find the side of the wall and get the x coord according to
 * the side of the wall hit
 * @param game The game struct
 * @param ray The ray struct
 * @note This function will be used to find the side of the wall
 * @note The wall texture is calculated based on 
 * the side of the wall that was hit. The wall_x is calculated based on the
 * position of the player and the direction of the ray. wall_x is used to
 * calculate the x coordinate of the texture that will be used to draw the wall
 * @note The Floor function to get the integer part of the wall_x
 * and then we Subtract it from wall_x to get the decimal part. This decimal
 * part is the x coord of in the tile side that was hit.
*/
void	find_tile_side_x(t_game *game, t_ray *ray)
{
	if (ray->side == NS)
	{
		if (ray->ray_dir_y < 0)
			ray->texture = SOUTH;
		else
			ray->texture = NORTH;
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_x < 0)
			ray->texture = EAST;
		else
			ray->texture = WEST;
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

/**
 * @brief Find the wall texture
 * @param game The game struct
 * @param ray The ray struct
 * @note This function will be used to find the wall texture
*/
void	find_wall_texture(t_game *game, t_ray *ray)
{
	ray->tile = game->map.map[ray->map_y][ray->map_x];
	find_tile_side_x(game, ray);
	find_tile_texture(game, ray);
}
