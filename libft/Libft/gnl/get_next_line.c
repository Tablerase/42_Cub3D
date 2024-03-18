/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:17:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 12:21:39 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*first_line(int fd, char *str, char *line)
{
	int	bytes_read;

	bytes_read = 1;
	line = ft_strjoin_gnl(str, line);
	while (bytes_read > 0 && ft_strchr_gnl(str, '\n') == NULL)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (line != NULL)
				free(line);
			return (NULL);
		}
		str[bytes_read] = '\0';
		line = ft_strjoin_gnl(str, line);
	}
	return (line);
}

char	*cut_line(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	new_line = malloc((i + 1) * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	prepare_next_line(char *str)
{
	int		i;
	int		j;
	char	str_cpy[BUFFER_SIZE + 1];

	i = 0;
	j = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		str[0] = '\0';
		return ;
	}
	while (str[i] != '\0')
		str_cpy[j++] = str[i++];
	str_cpy[j] = '\0';
	j = 0;
	i = 0;
	while (str_cpy[j] != '\0')
		str[i++] = str_cpy[j++];
	str[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = NULL;
	line = first_line(fd, str, line);
	if (line == NULL)
		return (NULL);
	line = cut_line(line);
	prepare_next_line(str);
	return (line);
}
