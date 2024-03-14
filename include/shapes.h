/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:42:33 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/13 17:27:44 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

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

/* ############################## PROTOTYPES ############################### */

// Line

void	draw_horizontal_line(t_img *img, t_point p1, t_point p2, int color);
void	draw_vertical_line(t_img *img, t_point p1, t_point p2, int color);
void	line(t_img *img, t_point p1, t_point p2, int color);

// Rectangle

void	rectangle(t_img *img, t_point start, t_point end, int color);
void	fill_rectangle(t_img *img, t_point start, t_point end, int color);

#endif