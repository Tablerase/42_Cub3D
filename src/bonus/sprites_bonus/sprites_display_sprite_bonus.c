/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_display_sprite_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:28:46 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 12:15:40 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	sprites_draw_stripe(
			t_game *game,
			int stripe,
			t_draw_sprite draw)
{
	int				y;
	int				d;
	unsigned int	color;
	char			*dest;
	char			*dest_img;

	y = draw.start_y - 1;
	while (++y < draw.end_y)
	{
		d = y * 256 - HEIGHT * 128 + game->sprite.sprite_height * 128;
		game->sprite.tex_y = ((d * game->sprite.img->on_screen->img.height)
				/ game->sprite.sprite_height) / 256;
		dest = game->sprite.img->on_screen->img.img.addr
			+ (game->sprite.tex_y
				* game->sprite.img->on_screen->img.img.line_len
				+ game->sprite.tex_x
				* (game->sprite.img->on_screen->img.img.bpp / 8));
		color = *(unsigned int *)dest;
		if (color != C_GREEN)
		{
			dest_img = game->img.addr + (y * game->img.line_len
					+ stripe * (game->img.bpp / 8));
			*(unsigned int *)dest_img = color;
		}
	}
}

void	raycasting_draw_sprite(t_game *game)
{
	int				i;
	int				stripe;
	t_draw_sprite	draw;

	fill_sprite_order_arrays(game);
	sort_sprites(game);
	i = 0;
	while (i < game->sprite.nb_sprites)
	{
		sprites_calculate(game, i);
		sprites_draw_size(game, &draw);
		stripe = draw.start_x - 1;
		while (++stripe < draw.end_x)
		{
			game->sprite.tex_x = sprites_tex_x_size(game, stripe, draw);
			if (game->sprite.transform_y > 0 && stripe > 0 && stripe < WIDTH
				&& game->sprite.transform_y < game->sprite.z_buffer[stripe])
				sprites_draw_stripe(game, stripe, draw);
		}
		i++;
	}
}
