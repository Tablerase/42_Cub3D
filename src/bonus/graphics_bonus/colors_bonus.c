/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:42:00 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/26 12:00:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Create an ARGB color
 * @param a The alpha (0 - 255)
 * @param r The red (0 - 255)
 * @param g The green (0 - 255)
 * @param b The blue (0 - 255)
 * @return The ARGB color
*/
int	create_argb(int a, int r, int g, int b)
{
	if (a < 0 || a > 255)
		a = 0;
	if (r < 0 || r > 255)
		r = 0;
	if (g < 0 || g > 255)
		g = 0;
	if (b < 0 || b > 255)
		b = 0;
	return (a << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief Get the alpha from an ARGB color
 * @param argb The ARGB color
 * @return The alpha
*/
int	get_alpha(int argb)
{
	return ((argb >> 24) & 0xFF);
}

/**
 * @brief Get the red from an ARGB color
 * @param argb The ARGB color
 * @return The red
*/
int	get_red(int argb)
{
	return ((argb >> 16) & 0xFF);
}

/**
 * @brief Get the green from an ARGB color
 * @param argb The ARGB color
 * @return The green
*/
int	get_green(int argb)
{
	return ((argb >> 8) & 0xFF);
}

/**
 * @brief Get the blue from an ARGB color
 * @param argb The ARGB color
 * @return The blue
*/
int	get_blue(int argb)
{
	return (argb & 0xFF);
}
