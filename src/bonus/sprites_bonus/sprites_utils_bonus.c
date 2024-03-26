/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:26:34 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 21:42:09 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	parsing_free_sprite(t_game *game)
{
	if (game->sprite.z_buffer != NULL)
		free(game->sprite.z_buffer);
	if (game->sprite.sprite_order != NULL)
		free(game->sprite.sprite_order);
	if (game->sprite.sprite_distance != NULL)
		free(game->sprite.sprite_distance);
	if (game->sprite.sprite_pos != NULL)
		free(game->sprite.sprite_pos);
	sprites_free_images(game);
}

void	sprites_free_images(t_game *game)
{
	t_sprite_list	*tmp;
	t_sprite_list	*tmp_to_free;

	if (game->sprite.img != NULL)
	{
		tmp = game->sprite.img;
		while (tmp->is_tail != true && tmp != NULL)
		{
			tmp_to_free = tmp;
			tmp = tmp->next;
			mlx_destroy_image(game->mlx.mlx, tmp_to_free->img.img.img);
			free(tmp_to_free);
		}
		if (tmp != NULL)
		{
			mlx_destroy_image(game->mlx.mlx, tmp->img.img.img);
			free(tmp);
		}
	}
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
	if(draw->start_x < 0)
		draw->start_x = 0;
	draw->end_x = draw->stripe_width / 2 + game->sprite.sprite_screen_x;
	if(draw->end_x >= WIDTH)
		draw->end_x = WIDTH - 1;
}
