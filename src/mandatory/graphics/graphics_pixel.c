/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:20:09 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/14 16:46:50 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/**
 * @brief Put a pixel to the image
 * @param img The image
 * @param x The x position
 * @param y The y position
 * @param color The color (in hexadecimal format - 0x00RRGGBB)
*/
void	pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return ;
	offset = (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = color;
}
