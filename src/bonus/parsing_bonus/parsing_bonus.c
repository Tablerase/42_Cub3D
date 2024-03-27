/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:32:22 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/26 21:22:01 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	parsing_file_name_and_format(t_game *game, char *filename)
{
	int	i;
	int	fd_dir;

	i = ft_strlen(filename);
	if (i < 4)
		parsing_exit_error(game, "Invalid file format\n");
	if (!(filename[--i] == 'b' && filename[--i] == 'u'
			&& filename[--i] == 'c' && filename[--i] == '.'))
		parsing_exit_error(game, "Invalid file format\n");
	fd_dir = open(filename, O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		parsing_exit_error(game, "Invalid file format\n");
	}
	return ;
}

void	parsing(t_game *game, char *filename)
{
	t_fds	fd;

	parsing_file_name_and_format(game, filename);
	fd.fd1 = open(filename, O_RDONLY);
	if (fd.fd1 == -1)
		parsing_exit_error(game, "Failed to open file\n");
	fd.fd2 = open(filename, O_RDONLY);
	if (fd.fd2 == -1)
	{
		close(fd.fd1);
		parsing_exit_error(game, "Failed to open file\n");
	}
	parsing_textures(game, fd);
	parse_map(game, fd);
	if (game->player.pos_x == -1 || game->player.pos_y == -1)
		parsing_exit_error(game, "No player position\n");
	parsing_allocate_sprite(game);
	return ;
}
