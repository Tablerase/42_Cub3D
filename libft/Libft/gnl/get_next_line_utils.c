/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:17:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 12:22:12 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (str == NULL)
		return (NULL);
	dest = malloc((ft_strlen_gnl(str) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*__free_line(char *line)
{
	free(line);
	return (NULL);
}

char	*ft_strjoin_gnl(char *str, char *line)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	if (*str == '\0')
		return (line);
	if (line == NULL)
		return (ft_strdup_gnl(str));
	dest = malloc((ft_strlen_gnl(str) + ft_strlen_gnl(line) + 1)
			* sizeof(char));
	if (dest == NULL)
		return (__free_line(line));
	while (line[i] != '\0')
		dest[j++] = line[i++];
	i = 0;
	while (str[i] != '\0')
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(line);
	return (dest);
}
