/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:09:33 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/25 11:33:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	is_char_to_trim(char c, char const *to_trim)
{
	int	i;

	i = 0;
	if (to_trim == NULL)
		return (0);
	while (to_trim[i] != '\0')
	{
		if (c == to_trim[i])
			return (1);
		i++;
	}
	return (0);
}

char	*right_strtrim(char *str, char *set)
{
	int		i;
	int		end;
	char	*dest;

	if (str == NULL)
		return (NULL);
	i = 0;
	end = ft_strlen(str) - 1;
	while (end > 0 && str[end] == '\n')
		end--;
	while (is_char_to_trim(str[end], set) && end > 0)
		end--;
	if (is_char_to_trim(str[end], set) == 0)
		end++;
	dest = malloc((end + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < end)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*right_trim_gnl(t_game *game, t_fds fd)
{
	char	*temp_buffer;
	char	*trimed_buffer;

	if (fd.fd1 != -1)
		temp_buffer = get_next_line(fd.fd1);
	else
		temp_buffer = get_next_line(fd.fd2);
	if (temp_buffer == NULL)
		return (NULL);
	trimed_buffer = right_strtrim(temp_buffer, " \n");
	free(temp_buffer);
	if (trimed_buffer == NULL)
	{
		if (fd.fd1 != -1)
			close(fd.fd1);
		close(fd.fd2);
		parsing_exit_error(game, "Buffer allocation failed\n");
	}
	return (trimed_buffer);
}

void	parsing_check_if_end_of_map(t_game *game, t_fds fd, char *prev_buffer)
{
	char	*buffer;

	buffer = right_trim_gnl(game, fd);
	while (buffer != NULL)
	{
		if (buffer[0] != '\0')
		{
			free(prev_buffer);
			free(buffer);
			close(fd.fd1);
			close(fd.fd2);
			parsing_exit_error(game, "Newline inside map\n");
		}
		free(buffer);
		buffer = right_trim_gnl(game, fd);
	}
	if (buffer != NULL)
		free(buffer);
	return ;
}

void	parsing_width_height_map(t_game *game, t_fds fd)
{
	char	*buffer;
	int		len_buffer;

	buffer = right_trim_gnl(game, fd);
	while (buffer != NULL && buffer[0] == '\0')
	{
		free(buffer);
		buffer = right_trim_gnl(game, fd);
	}
	while (buffer != NULL && buffer[0] != '\0')
	{
		game->map.height++;
		len_buffer = ft_strlen(buffer);
		if (len_buffer > game->map.width)
			game->map.width = len_buffer;
		free(buffer);
		buffer = right_trim_gnl(game, fd);
	}
	if (buffer != NULL && buffer[0] == '\0')
		parsing_check_if_end_of_map(game, fd, buffer);
	if (buffer != NULL)
		free(buffer);
}
