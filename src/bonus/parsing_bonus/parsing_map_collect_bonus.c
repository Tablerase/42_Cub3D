/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_collect_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:15:20 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 20:56:48 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	parsing_fill_submap(t_game *game, char *buffer, int i, t_fds fd)
{
	int	j;

	j = 0;
	while (buffer[j] != '\0')
	{
		if (buffer[j] == '0')
			game->map.map[i][j] = GROUND;
		else if (buffer[j] == '1')
			game->map.map[i][j] = WALL;
		else if (buffer[j] == ' ')
			game->map.map[i][j] = EMPTY;
		else if (buffer[j] == 'N' || buffer[j] == 'S'
			|| buffer[j] == 'E' || buffer[j] == 'W')
			parsing_found_player(game, buffer[j], i, j);
		else if (buffer[j] == '2')
		{
			game->map.map[i][j] = SPRITE;
			game->sprite.sprite_pos[game->sprite.nb_sprites].x = (double)j + 0.5;
			game->sprite.sprite_pos[game->sprite.nb_sprites].y = (double)i + 0.5;
			game->sprite.nb_sprites++;
		}
		else
		{
			free(buffer);
			close(fd.fd2);
			parsing_exit_error(game, "Invalid map character\n");
		}
		j++;
	}
	while (j < game->map.width)
		game->map.map[i][j++] = EMPTY;
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
