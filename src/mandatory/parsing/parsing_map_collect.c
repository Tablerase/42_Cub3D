/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_collect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:15:20 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 14:36:49 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
			game->map.map[i][j] = PLAYER;
		else
		{
			free(buffer);
			close(fd.fd2);
			parsing_exit_error(game);
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
		parsing_exit_error(game);
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
