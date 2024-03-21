/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:28:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/21 14:29:51 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/**
 * @brief Draw the texture line
 * @param game The game struct
 * @param ray The ray struct
 * @note The tex_y is calculated based on the tex_coord and the height of the
 * texture, a mask is applied to prevent overflow - & (texture->height - 1)
 * will truncate every value greater than the height of the texture
 * @note The tex_step increases the tex_coord based on the line_height
 * @note The tex_coord is initialized centered on the screen and then
 * it is increased based on the line_height
 * and step to draw the texture at scale
*/
void	draw_texture_line(t_game *game, t_ray *ray)
{
	int		offset;
	int		offset_texture;
	int		y;
	int		x;

	y = 0;
	x = ray->x;
	// Draw ceiling
	while (y < HEIGHT - ray->draw_end)
	{
		if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
			break ;
		offset = (y * game->img.line_len + x * (game->img.bpp / 8));
		*(unsigned int *)(game->img.addr + offset) = game->textures.ceiling_color;
		y++;
	}
	// Draw wall
	ray->tex_step = 1.0 * ray->texture->height / ray->line_height;
	ray->tex_coord = (ray->draw_start - HEIGHT / 2
			+ ray->line_height / 2) * ray->tex_step;
	while (y < HEIGHT - ray->draw_start)
	{
		ray->tex_y = (int)ray->tex_coord & (ray->texture->height - 1);
		ray->tex_coord += ray->tex_step;
		offset = (y * game->img.line_len + x * (game->img.bpp / 8));
		offset_texture = (int)ray->tex_y * ray->texture->img.line_len + ray->tex_x * (ray->texture->img.bpp / 8);
		*(unsigned int *)(game->img.addr + offset) = *(unsigned int *)(ray->texture->img.addr + offset_texture);
		y++;
	}
	// Draw floor
	while (y < HEIGHT)
	{
		offset = (y * game->img.line_len + x * (game->img.bpp / 8));
		*(unsigned int *)(game->img.addr + offset) = game->textures.floor_color;
		y++;
	}
}
