/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:42:01 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 15:24:35 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Initialization of the ray
 * @param game The game struct
 * @param ray The ray struct
 * @note The division are protected against division by zero (0.0000001)
 * @note The camera_x is calculated based on the x position according to the
 * width of the screen
 * @note The ray_dir_x and ray_dir_y are calculated based on the direction of
 * the player and the plane
*/
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->x = x;
	ray->y = 0;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = game->player.pos_x;
	ray->map_y = game->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->ray_dir_x = 0.0000001;
	if (ray->ray_dir_y == 0)
		ray->ray_dir_y = 0.0000001;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = false;
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->color = create_argb(0, 10, 200, 80);
}

/**
 * @brief Initialization of the steps and side_dist
 * @param game The game struct
 * @param ray The ray struct
 * @note This function will be used to calculate the steps of the ray
 * and the side_dist
 * @note The steps are calculated based on the direction of the ray and
 * the side_dist is calculated based on the position of the player and the
 * direction of the ray
*/
static void	init_side_dist_and_step(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

/**
 * @brief DDA algorithm
 * @param game The game struct
 * @param ray The ray struct
 * @note The ray travels each cell in the map grid and checks if it hits a wall
 * if it doesn't, it continues to the next cell according to the 
 * slope of the ray previously calculated.
 * Each step, the side_dist is incremented by the side_dist
 * value and the map_x or map_y is incremented by the step_x or step_y value.
 * @note This allows to know the distance to the wall and the side of the wall
 * that was hit
*/
static void	dda_algorithm(t_game *game, t_ray *ray)
{
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = NS;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = EW;
		}
		if (game->map.map[ray->map_y][ray->map_x] == WALL
			|| game->map.map[ray->map_y][ray->map_x] == DOOR_CLOSED)
			ray->hit = true;
	}
}

/**
 * @brief Raycasting function
 * @param game The game struct
 * @note This function will be used to cast rays and render the game
*/
void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		init_side_dist_and_step(game, &ray);
		dda_algorithm(game, &ray);
		calculate_perp_wall_dist(&ray);
		calculate_line_params(&ray);
		find_wall_texture(game, &ray);
		draw_texture_line(game, &ray);
		if (game->sprite.nb_sprites != 0)
			game->sprite.z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
	if (game->sprite.nb_sprites == 0)
		return ;
	raycasting_draw_sprite(game);
}
