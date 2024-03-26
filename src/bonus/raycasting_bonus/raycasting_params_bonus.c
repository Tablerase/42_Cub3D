/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_params_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:03:28 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 12:00:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Calculation of the perpendicular wall distance
 * @param ray The ray struct
 * @note The side_dist is almost the perpendicular wall distance, we just need
 * to substract the delta_dist because the dda algorithm will always stop in the
 * first wall it encounters (so the side_dist go in the wall)
 * @note Horizontal wall (NS) distance is calculated based on the side_dist_x and
 * delta_dist_x
 * @note Vertical wall (EW) distance is calculated based on the side_dist_y and
 * delta_dist_y
*/
void	calculate_perp_wall_dist(t_ray *ray)
{
	if (ray->side == NS)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

/**
 * @brief Calculation of the line parameters
 * @param ray The ray struct
 * @note The line height is calculated based on the perpendicular wall distance
 * and the height of the screen
 * @note The draw_start and draw_end are calculated based on the line_height
 * and the height of the screen and are protected against out of bounds
 * @note The line is centered on the screen
*/
void	calculate_line_params(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

/**
 * @brief Find the wall color
 * @param game The game struct
 * @param ray The ray struct
 * @note The wall color is calculated based on the side of the wall that was hit
 * and the step_x and step_y values
 * @note The side will have a different brightness according to the direction
*/
void	find_wall_color(t_game *game, t_ray *ray)
{
	if (game->map.map[ray->map_y][ray->map_x] == WALL)
	{
		if (ray->side == EW)
		{
			if (ray->step_x == -1)
				ray->color = create_argb(0, 0, 0, 255);
			else
				ray->color = create_argb(0, 0, 255, 0);
		}
		else
		{
			if (ray->step_y == -1)
				ray->color = create_argb(0, 255, 255, 0);
			else
				ray->color = create_argb(0, 255, 0, 255);
		}
	}
	else
	{
		ray->color = create_argb(0, 255, 0, 0);
	}
}
