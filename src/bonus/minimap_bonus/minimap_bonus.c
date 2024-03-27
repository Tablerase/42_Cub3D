/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:58:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 15:36:22 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	transparency(int alpha, int color, int background_color)
{
	int	transparent_r;
	int	transparent_g;
	int	transparent_b;

	transparent_r = ((color >> 16) * alpha / 255) + (background_color >> 16)
		* (255 - alpha) / 255;
	transparent_g = (((color >> 8) - ((color >> 16) << 8)) * alpha / 255)
		+ ((background_color >> 8) - ((background_color >> 16) << 8))
		* (255 - alpha) / 255;
	transparent_b = ((color % 256) * alpha / 255) + (background_color % 256)
		* (255 - alpha) / 255;
	return (transparent_r << 16 | transparent_g << 8 | transparent_b);
}

void	minimap_cell_color(t_game *game, t_minimap *m, int i, int j)
{
	if (!(i >= 0 && i < game->map.height && j >= 0 && j < game->map.width)
		|| game->map.map[i][j] == EMPTY)
	{
		m->color = transparency(127, C_WHITE, *(unsigned int *)(game->img.addr
					+ (m->pixel_y * game->img.line_len + m->pixel_x
						* (game->img.bpp / 8))));
	}
	else if (game->map.map[i][j] == DOOR_OPEN
		|| game->map.map[i][j] == DOOR_CLOSED)
		m->color = 0x468499;
	else if (game->map.map[i][j] == GROUND)
		m->color = C_CLEAR_BROWN;
	else if (game->map.map[i][j] == WALL)
		m->color = C_BLACK;
	else if (game->map.map[i][j] == SPRITE)
		m->color = C_TEAL;
	else if (game->map.map[i][j] != EMPTY)
		m->color = C_BLUE;
	if (j == (int)game->player.pos_x && i == (int)game->player.pos_y)
		m->color = C_RED;
}

void	minimap_cell_draw(t_game *game, t_minimap *m, int nb_pixel_per_cell)
{
	char	*dest;
	int		x;
	int		y;

	x = m->pixel_x;
	while (x < m->pixel_x + nb_pixel_per_cell)
	{
		y = m->pixel_y;
		while (y < m->pixel_y + nb_pixel_per_cell)
		{
			dest = game->img.addr + (y * game->img.line_len
					+ x * game->img.bpp / 8);
			if (minimap_wall_and_border(m, x, y, nb_pixel_per_cell))
				*(unsigned int *)dest = 0x8b4513;
			else if (minimap_sprite_and_border(m, x, y, nb_pixel_per_cell))
				*(unsigned int *)dest = C_CLEAR_BROWN;
			else
				*(unsigned int *)dest = m->color;
			y++;
		}
		x++;
	}
}

void	minimap(t_game *game)
{
	t_minimap	m;
	int			i;
	int			j;
	int			nb_pixel_per_cell;

	nb_pixel_per_cell = 5;
	minimap_init(game, &m);
	i = m.start_i;
	while (i < m.end_i)
	{
		j = m.start_j;
		m.pixel_x = 10;
		m.pixel_y += nb_pixel_per_cell;
		while (j < m.end_j)
		{
			minimap_cell_color(game, &m, i, j);
			if (m.color != -1)
				minimap_cell_draw(game, &m, nb_pixel_per_cell);
			m.pixel_x += nb_pixel_per_cell;
			j++;
		}
		i++;
	}
}
