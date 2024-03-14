/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:50:17 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/10 18:48:53 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rectangle(t_img *img, t_point start, t_point end, int color)
{
	int	x;
	int	y;

	x = start.x;
	while (x < end.x)
	{
		pixel_put(img, x, start.y, color);
		pixel_put(img, x, end.y, color);
		x++;
	}
	y = start.y;
	while (y < end.y)
	{
		pixel_put(img, start.x, y, color);
		pixel_put(img, end.x, y, color);
		y++;
	}
}

void	fill_rectangle(t_img *img, t_point start, t_point end, int color)
{
	int	x;
	int	y;

	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
		{
			pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}
