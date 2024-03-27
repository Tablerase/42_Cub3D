/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:26:34 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 12:16:16 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	fill_sprite_order_arrays(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite.nb_sprites)
	{
		game->sprite.sprite_order[i] = i;
		game->sprite.sprite_distance[i] = distance_sprite_to_player(game, i);
		i++;
	}
}

void	sprite_exchange(t_game *game, int i, int j)
{
	double	temp_dist;
	int		temp_order;

	temp_dist = game->sprite.sprite_distance[i];
	temp_order = game->sprite.sprite_order[i];
	game->sprite.sprite_distance[i] = game->sprite.sprite_distance[j];
	game->sprite.sprite_order[i] = game->sprite.sprite_order[j];
	game->sprite.sprite_distance[j] = temp_dist;
	game->sprite.sprite_order[j] = temp_order;
}

void	sort_sprites(t_game *game)
{
	int	i;
	int	j;
	int	min;

	i = 0;
	while (i < game->sprite.nb_sprites)
	{
		j = i;
		min = j;
		while (j < game->sprite.nb_sprites)
		{
			if (game->sprite.sprite_distance[j]
				> game->sprite.sprite_distance[min])
				min = j;
			j++;
		}
		sprite_exchange(game, i, min);
		i++;
	}
}

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
