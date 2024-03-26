/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_shapes_lines_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:52:21 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 12:00:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Function that returns the sign of a number
 * @param val The value
 * @return The sign of the number
 * @note val < 0 = -1
 * @note val == 0 = 0
 * @note val > 0 = 1
*/
static int	sgn(int val)
{
	return ((0 < val) - (val < 0));
}

void	draw_horizontal_line(t_img *img, t_point p1, t_point p2, int color)
{
	int		i;
	t_line	line;

	line.dist_x = p2.x - p1.x;
	line.dist_y = p2.y - p1.y;
	line.magnitude_x = abs(line.dist_x);
	line.magnitude_y = abs(line.dist_y);
	line.sign_x = sgn(line.dist_x);
	line.sign_y = sgn(line.dist_y);
	line.y = line.magnitude_x >> 1;
	line.px = p1.x;
	line.py = p1.y;
	i = -1;
	while (++i < line.magnitude_x)
	{
		pixel_put(img, line.px, line.py, color);
		line.y += line.magnitude_y;
		if (line.y >= line.magnitude_x)
		{
			line.y -= line.magnitude_x;
			line.py += line.sign_y;
		}
		line.px += line.sign_x;
	}
}

/**
 * @brief Function to draw a vertical line
 * @note We use a bitwise shift to divide the magnitude_x by 2 (more efficient)
*/
void	draw_vertical_line(t_img *img, t_point p1, t_point p2, int color)
{
	int		i;
	t_line	line;

	line.dist_x = p2.x - p1.x;
	line.dist_y = p2.y - p1.y;
	line.magnitude_x = abs(line.dist_x);
	line.magnitude_y = abs(line.dist_y);
	line.sign_x = sgn(line.dist_x);
	line.sign_y = sgn(line.dist_y);
	line.x = line.magnitude_y >> 1;
	line.px = p1.x;
	line.py = p1.y;
	i = -1;
	while (++i < line.magnitude_y)
	{
		pixel_put(img, line.px, line.py, color);
		line.x += line.magnitude_x;
		if (line.x >= line.magnitude_y)
		{
			line.x -= line.magnitude_y;
			line.px += line.sign_x;
		}
		line.py += line.sign_y;
	}
}

/**
 * @brief Function to draw a line
 * @param img The image
 * @param p1 The first point
 * @param p2 The second point
 * @param color The color
 * @note Bresenham's line algorithm
*/
void	line(t_img *img, t_point p1, t_point p2, int color)
{
	int	dx;
	int	dy;
	int	dxabs;
	int	dyabs;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dxabs = abs(dx);
	dyabs = abs(dy);
	if (dxabs >= dyabs)
		draw_horizontal_line(img, p1, p2, color);
	else
		draw_vertical_line(img, p1, p2, color);
}
