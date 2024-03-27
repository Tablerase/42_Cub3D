/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_times_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:22 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/27 17:19:46 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

/**
 * @brief Function to change the sprite image
 * @param game The game struct
 * @note Changes the sprite image every 8 frames
*/
void	change_image_sprite(t_game *game)
{
	static int	time;

	if (time > 7)
	{
		time = 0;
		game->sprite.img->on_screen->is_on_screen = false;
		game->sprite.img->on_screen = game->sprite.img->on_screen->next;
		game->sprite.img->on_screen->is_on_screen = true;
	}
	time++;
}
