/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_display_sprite_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:28:46 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 21:46:26 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	sprites_calculate(t_game *game, int i)
{
	game->sprite.sprite_x = game->sprite.sprite_pos[game->sprite.sprite_order[i]].x - game->player.pos_x;
	game->sprite.sprite_y = game->sprite.sprite_pos[game->sprite.sprite_order[i]].y - game->player.pos_y;
	game->sprite.inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.plane_y * game->player.dir_x);
	game->sprite.transform_x = game->sprite.inv_det * (game->player.dir_y * game->sprite.sprite_x - game->player.dir_x * game->sprite.sprite_y);
	game->sprite.transform_y = game->sprite.inv_det * (-game->player.plane_y * game->sprite.sprite_x + game->player.plane_x * game->sprite.sprite_y);
	game->sprite.sprite_screen_x = (int)((WIDTH / 2) * (1 + game->sprite.transform_x / game->sprite.transform_y));
	game->sprite.sprite_height = abs((int)(HEIGHT / game->sprite.transform_y));
}

void	sprites_draw_stripe(t_game *game, int stripe, t_draw_sprite draw, float time)
{
	int	screen_y;

	for (int y = draw.start_y; y < draw.end_y; y++)
	{
		int d = y * 256 - HEIGHT * 128 + game->sprite.sprite_height * 128;
		game->sprite.tex_y = ((d * game->sprite.img->on_screen->img.height)
			/ game->sprite.sprite_height) / 256;
		char *dest = game->sprite.img->on_screen->img.img.addr
			+ (game->sprite.tex_y * game->sprite.img->on_screen->img.img.line_len
			+ game->sprite.tex_x * (game->sprite.img->on_screen->img.img.bpp / 8));
		unsigned int color = *(unsigned int *)dest;
		if (color != C_GREEN)
		{
			screen_y = y;
			if (y - (int)time >= 0)
				screen_y = y - (int)time;
			char *dest_img = game->img.addr + (screen_y * game->img.line_len
				+ stripe * (game->img.bpp / 8));
			*(unsigned int *)dest_img = color;
		}
	}
}
