/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:08:46 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 15:09:17 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	parsing_count_digits(char *color_rgb, int *i)
{
	int	j;
	int	res;

	j = 0;
	while (color_rgb[j] == '0')
		j++;
	if (j != 0 && (color_rgb[j] == '\0' || color_rgb[j] == ','))
	{
		(*i) += j - 1;
		return (1);
	}
	res = 0;
	while (ft_isdigit(color_rgb[j + res]) == 1)
		res++;
	(*i) += j + res - 1;
	if (res == 0)
		return (4);
	if (color_rgb[j + res] == ',' || color_rgb[j + res] == '\0')
		return (res);
	return (4);
}

void	parsing_free_color(t_game *game, char *color_rgb, t_fds fd)
{
	close(fd.fd1);
	close(fd.fd2);
	free(color_rgb);
	parsing_exit_error(game);
}
