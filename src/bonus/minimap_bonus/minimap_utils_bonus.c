/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:58:03 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 16:56:50 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

bool	minimap_wall_and_border(
			t_minimap *m,
			int x,
			int y,
			int nb_pixel_per_cell)
{
	if (m->color == C_BLACK && x != m->pixel_x
		&& x != m->pixel_x + nb_pixel_per_cell - 1
		&& y != m->pixel_y && y != m->pixel_y + nb_pixel_per_cell - 1)
		return (true);
	return (false);
}

bool	minimap_sprite_and_border(
			t_minimap *m,
			int x,
			int y,
			int nb_pixel_per_cell)
{
	if (m->color == C_TEAL && (x == m->pixel_x
			|| x == m->pixel_x + nb_pixel_per_cell - 1
			|| y == m->pixel_y || y == m->pixel_y + nb_pixel_per_cell - 1))
		return (true);
	return (false);
}

bool	minimap_door_and_border(
			t_minimap *m,
			int x,
			int y,
			int nb_pixel_per_cell)
{
	if (m->color == C_RED)
	{
		if (y - m->pixel_y == x - m->pixel_x
			|| y - m->pixel_y + x - m->pixel_x == nb_pixel_per_cell - 1)
			return (false);
		return (true);
	}
	return (false);
}

void	minimap_init(t_game *game, t_minimap *m)
{
	m->pixel_x = 10;
	m->pixel_y = 10;
	m->start_i = game->player.pos_y - 15;
	m->end_i = m->start_i + 30;
	m->start_j = game->player.pos_x - 15;
	m->end_j = m->start_j + 30;
	m->color = 0x000000;
}
