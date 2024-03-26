/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:43:43 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/25 12:17:14 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

char	*trimed_gnl(t_game *game, t_fds fd, const char *to_trim)
{
	char	*trimed_buffer;
	char	*temp_buffer;

	temp_buffer = get_next_line(fd.fd1);
	if (temp_buffer == NULL)
		return (NULL);
	trimed_buffer = ft_strtrim(temp_buffer, to_trim);
	free(temp_buffer);
	if (trimed_buffer == NULL)
		parsing_free_error_textures(game, fd, NULL, 4);
	temp_buffer = get_next_line(fd.fd2);
	if (temp_buffer == NULL)
		parsing_free_error_textures(game, fd, trimed_buffer, 4);
	free(temp_buffer);
	return (trimed_buffer);
}

char	*parsing_add_count(t_count_id *nb_textures, char *identifier)
{
	if (ft_strcmp("NO", identifier) == 0)
		nb_textures->no++;
	else if (ft_strcmp("SO", identifier) == 0)
		nb_textures->so++;
	else if (ft_strcmp("WE", identifier) == 0)
		nb_textures->we++;
	else if (ft_strcmp("EA", identifier) == 0)
		nb_textures->ea++;
	else if (ft_strcmp("F", identifier) == 0)
		nb_textures->f++;
	else if (ft_strcmp("C", identifier) == 0)
		nb_textures->c++;
	return (identifier);
}

int	count_id(t_count_id nb_textures)
{
	if (nb_textures.no > 1)
		return (-1);
	if (nb_textures.so > 1)
		return (-1);
	if (nb_textures.we > 1)
		return (-1);
	if (nb_textures.ea > 1)
		return (-1);
	if (nb_textures.f > 1)
		return (-1);
	if (nb_textures.c > 1)
		return (-1);
	return (nb_textures.no + nb_textures.so
		+ nb_textures.we + nb_textures.ea
		+ nb_textures.f + nb_textures.c);
}

char	*parsing_found_identifier(char *buffer, t_count_id *nb_textures)
{
	if (ft_strlen(buffer) < 2)
		return (NULL);
	if (ft_strncmp(buffer, "NO", 2) == 0
		&& (buffer[2] == ' ' || buffer[2] == '\0'))
		return (parsing_add_count(nb_textures, "NO"));
	if (ft_strncmp(buffer, "SO", 2) == 0
		&& (buffer[2] == ' ' || buffer[2] == '\0'))
		return (parsing_add_count(nb_textures, "SO"));
	if (ft_strncmp(buffer, "WE", 2) == 0
		&& (buffer[2] == ' ' || buffer[2] == '\0'))
		return (parsing_add_count(nb_textures, "WE"));
	if (ft_strncmp(buffer, "EA", 2) == 0
		&& (buffer[2] == ' ' || buffer[2] == '\0'))
		return (parsing_add_count(nb_textures, "EA"));
	if (ft_strncmp(buffer, "F", 1) == 0
		&& (buffer[1] == ' ' || buffer[1] == '\0'))
		return (parsing_add_count(nb_textures, "F"));
	if (ft_strncmp(buffer, "C", 1) == 0
		&& (buffer[1] == ' ' || buffer[1] == '\0'))
		return (parsing_add_count(nb_textures, "C"));
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned int)s1[i] - (unsigned int)s2[i]);
}
