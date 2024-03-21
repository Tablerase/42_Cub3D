/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:42:53 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/21 14:32:37 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_set_texture(
			t_game *game,
			char **buffer,
			char *identifier,
			t_fds fd)
{
	char	*texture_path;

	texture_path = ft_strtrim(&(*buffer)[ft_strlen(identifier)], " \n");
	free(*buffer);
	*buffer = NULL;
	if (texture_path == NULL || texture_path[0] == '\0')
		parsing_free_error_textures(game, fd, texture_path);
	if (ft_strcmp("NO", identifier) == 0)
		allocate_data_texture(game, &(game->textures.north),
			texture_path, fd);
	else if (ft_strcmp("SO", identifier) == 0)
		allocate_data_texture(game, &(game->textures.south),
			texture_path, fd);
	else if (ft_strcmp("WE", identifier) == 0)
		allocate_data_texture(game, &(game->textures.west),
			texture_path, fd);
	else if (ft_strcmp("EA", identifier) == 0)
		allocate_data_texture(game, &(game->textures.east),
			texture_path, fd);
	else if (ft_strcmp("F", identifier) == 0)
		parsing_set_color(game, identifier, texture_path, fd);
	else if (ft_strcmp("C", identifier) == 0)
		parsing_set_color(game, identifier, texture_path, fd);
	free(texture_path);
	return ;
}

void	parsing_init_count_id(t_count_id *nb_textures)
{
	nb_textures->no = 0;
	nb_textures->so = 0;
	nb_textures->we = 0;
	nb_textures->ea = 0;
	nb_textures->f = 0;
	nb_textures->c = 0;
}

void	parsing_textures(t_game *game, t_fds fd)
{
	t_count_id	nb_textures;
	char		*buffer;
	char		*identifier;

	parsing_init_count_id(&nb_textures);
	buffer = trimed_gnl(fd, " \n");
	while (buffer != NULL)
	{
		identifier = parsing_found_identifier(buffer, &nb_textures);
		if (identifier != NULL && count_id(nb_textures) != -1)
			parsing_set_texture(game, &buffer, identifier, fd);
		else if (buffer[0] != '\0')
			parsing_free_error_textures(game, fd, buffer);
		else
			free(buffer);
		if (count_id(nb_textures) == 6 || count_id(nb_textures) == -1)
			break ;
		buffer = trimed_gnl(fd, " \n");
	}
	if (buffer != NULL)
		free(buffer);
	if (count_id(nb_textures) != 6)
		parsing_free_error_textures(game, fd, NULL);
	return ;
}

void	allocate_data_texture(
		t_game *game,
		t_texture *face,
		char *texture_path,
		t_fds fd)
{
	face->img.img = mlx_xpm_file_to_image(game->mlx.mlx, texture_path,
			&face->width, &face->height);
	if (face->img.img == NULL)
	{
		parsing_free_error_textures(game, fd, texture_path);
	}
	face->img.addr = mlx_get_data_addr(face->img.img, &face->img.bpp,
			&face->img.line_len, &face->img.endian);
	if (face->img.addr == NULL)
	{
		parsing_free_error_textures(game, fd, texture_path);
	}
	return ;
}

void	parsing_free_error_textures(t_game *game, t_fds fd, char *buffer)
{
	if (buffer != NULL)
		free(buffer);
	close(fd.fd1);
	close(fd.fd2);
	parsing_exit_error(game);
}
