/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:42:33 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/15 15:05:22 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

/* ############################## INCLUDES ############################### */

# include "cub3d.h"

/* ############################## STRUCTURES ############################### */

/**
 * @brief Struct of a point
 * @param x The x position
 * @param y The y position
*/
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/**
 * @brief Struct for the line
 * @note Store data need to create a line
*/
typedef struct s_line
{
	int	dist_x;
	int	dist_y;
	int	magnitude_x;
	int	magnitude_y;
	int	sign_x;
	int	sign_y;
	int	x;
	int	y;
	int	px;
	int	py;
}	t_line;

#endif