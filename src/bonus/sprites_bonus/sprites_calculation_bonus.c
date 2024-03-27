/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_calcluation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:13:01 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 12:17:21 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	sprites_calculate(t_game *game, int i)
{
	t_sprite_pos	sprite_pos;

	sprite_pos = game->sprite.sprite_pos[game->sprite.sprite_order[i]];
	game->sprite.sprite_x = sprite_pos.x - game->player.pos_x;
	game->sprite.sprite_y = sprite_pos.y - game->player.pos_y;
	game->sprite.inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.plane_y * game->player.dir_x);
	game->sprite.transform_x = game->sprite.inv_det
		* (game->player.dir_y * game->sprite.sprite_x
			- game->player.dir_x * game->sprite.sprite_y);
	game->sprite.transform_y = game->sprite.inv_det
		* (-game->player.plane_y * game->sprite.sprite_x
			+ game->player.plane_x * game->sprite.sprite_y);
	game->sprite.sprite_screen_x = (int)((WIDTH / 2)
			* (1 + game->sprite.transform_x / game->sprite.transform_y));
	game->sprite.sprite_height = abs((int)(HEIGHT / game->sprite.transform_y));
}

double	distance_sprite_to_player(t_game *game, int i)
{
	double	dist;

	dist = pow(game->player.pos_x - game->sprite.sprite_pos[i].x, 2)
		+ pow(game->player.pos_y - game->sprite.sprite_pos[i].y, 2);
	return (dist);
}

void	sprites_draw_size(t_game *game, t_draw_sprite *draw)
{
	draw->start_y = -game->sprite.sprite_height / 2 + HEIGHT / 2;
	if (draw->start_y < 0)
		draw->start_y = 0;
	draw->end_y = game->sprite.sprite_height / 2 + HEIGHT / 2;
	if (draw->end_y >= HEIGHT)
		draw->end_y = HEIGHT - 1;
	draw->stripe_width = abs((int)(HEIGHT / game->sprite.transform_y));
	draw->start_x = -draw->stripe_width / 2 + game->sprite.sprite_screen_x;
	if (draw->start_x < 0)
		draw->start_x = 0;
	draw->end_x = draw->stripe_width / 2 + game->sprite.sprite_screen_x;
	if (draw->end_x >= WIDTH)
		draw->end_x = WIDTH - 1;
}

int	sprites_tex_x_size(t_game *game, int stripe, t_draw_sprite draw)
{
	int	tex_x;

	tex_x = (int)(256 * (stripe - (-draw.stripe_width
					/ 2 + game->sprite.sprite_screen_x))
			* game->sprite.img->on_screen->img.width / draw.stripe_width) / 256;
	return (tex_x);
}
