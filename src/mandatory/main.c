/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/13 17:24:32 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initialization of the ray
 * @param game The game struct
 * @param ray The ray struct
 * @param x The x position
 * @note This function will be used to initialize the ray
 * @note The division are protected against division by zero
 * @note The camera_x is calculated based on the x position according to the
 * width of the screen
 * @note The ray_dir_x and ray_dir_y are calculated based on the direction of
 * the player and the plane
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = game->player.pos_x;
	ray->map_y = game->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->ray_dir_x = INFINITY;
	if (ray->ray_dir_y == 0)
		ray->ray_dir_y = INFINITY;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = false;
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
void	init_side_dist_and_step(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
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
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
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
 * if it doesn't, it continues to the next cell according to the slope of the ray
 * previously calculated. Each step, the side_dist is incremented by the side_dist
 * value and the map_x or map_y is incremented by the step_x or step_y value.
 * @note This allows to know the distance to the wall and the side of the wall
 * that was hit
*/
void	dda_algorithm(t_game *game, t_ray *ray)
{
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = EW;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = NS;
		}
		if (game->map.map[ray->map_y][ray->map_x] == WALL)
			ray->hit = true;
	}
}

/**
 * @brief Calculation of the perpendicular wall distance
 * @param game The game struct
 * @param ray The ray struct
 * @note This function will be used to calculate the perpendicular wall distance
 * @note The perpendicular wall distance is calculated based on the side of the wall
 * that was hit and the side_dist and delta_dist values
*/
void	calculate_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == EW)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

/**
 * @brief Calculation of the line parameters
 * @param game The game struct
 * @param ray The ray struct
 * @note This function will be used to calculate the line parameters
 * @note The line height is calculated based on the perpendicular wall distance
 * and the height of the screen
 * @note The draw_start and draw_end are calculated based on the line_height
 * and the height of the screen and are protected against out of bounds
 * @note The line is centered on the screen
*/
void	calculate_line_params(t_game *game, t_ray *ray)
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
 * @note This function will be used to find the wall color
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
	if (ray->side == EW)
		ray->color = ray->color / 2;
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
		calculate_perp_wall_dist(game, &ray);
		calculate_line_params(game, &ray);
		find_wall_color(game, &ray);
		draw_vertical_line(
			&game->img, (t_point){x, ray.draw_start},
			(t_point){x, ray.draw_end}, ray.color);
		x++;
	}
}

int	main(void)
{
	t_game	game;

	if (ft_setup_player(&game) == false)
		return (EXIT_FAILURE);
	if (ft_setup_map(&game) == false)
		return (EXIT_FAILURE);
	if (ft_setup(&game) == false)
		return (EXIT_FAILURE);
	ft_events(&game);
	mlx_loop(game.mlx.mlx);
	ft_exit(&game);
	return (0);
}
