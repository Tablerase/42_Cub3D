/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_collect_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:15:20 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 15:39:04 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	parsing_fill_submap(t_game *game, char *buffer, int i, t_fds fd)
{
	int	j;

	j = -1;
	while (buffer[++j] != '\0')
	{
		if (buffer[j] >= '0' && buffer[j] <= '4')
			parsing_found_texture(game, buffer[j], i, j);
		else if (buffer[j] == ' ')
			game->map.map[i][j] = EMPTY;
		else if (buffer[j] == 'N' || buffer[j] == 'S'
			|| buffer[j] == 'E' || buffer[j] == 'W')
			parsing_found_player(game, buffer[j], i, j);
		else
		{
			free(buffer);
			close(fd.fd2);
			parsing_exit_error(game, "Invalid map character\n");
		}
	}
	while (j < game->map.width)
		game->map.map[i][j++] = EMPTY;
}

void	parsing_found_texture(t_game *game, char c, int i, int j)
{
	if (c == '0')
		game->map.map[i][j] = GROUND;
	else if (c == '1')
		game->map.map[i][j] = WALL;
	else if (c == '2')
		game->map.map[i][j] = DOOR_CLOSED;
	else if (c == '3')
		game->map.map[i][j] = DOOR_OPEN;
	else if (c == '4')
		parsing_found_sprite(game, i, j);
}

void	parsing_found_sprite(t_game *game, int i, int j)
{
	int				index;
	t_sprite_pos	*sprite_pos;

	game->map.map[i][j] = SPRITE;
	sprite_pos = malloc((game->sprite.nb_sprites + 1) * sizeof(t_sprite_pos));
	if (sprite_pos == NULL)
		parsing_exit_error(game, "Allocation failed\n");
	index = 0;
	while (index < game->sprite.nb_sprites)
	{
		sprite_pos[index].x = game->sprite.sprite_pos[index].x;
		sprite_pos[index].y = game->sprite.sprite_pos[index].y;
		index++;
	}
	if (game->sprite.sprite_pos != NULL)
		free(game->sprite.sprite_pos);
	sprite_pos[index].x = (double)j + 0.5;
	sprite_pos[index].y = (double)i + 0.5;
	game->sprite.sprite_pos = sprite_pos;
	game->sprite.nb_sprites++;
}

void	parsing_collect_map(t_game *game, t_fds fd)
{
	int		i;
	char	*buffer;

	buffer = right_trim_gnl(game, fd);
	while (buffer != NULL && buffer[0] == '\0')
	{
		free(buffer);
		buffer = right_trim_gnl(game, fd);
	}
	if (buffer == NULL)
	{
		close(fd.fd2);
		parsing_exit_error(game, "Empty map\n");
	}
	i = 0;
	while (buffer != NULL && i < game->map.height)
	{
		parsing_fill_submap(game, buffer, i++, fd);
		free(buffer);
		buffer = right_trim_gnl(game, fd);
	}
	if (buffer != NULL)
		free(buffer);
}
